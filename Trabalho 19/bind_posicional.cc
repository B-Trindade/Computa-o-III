/*

  Altere a função bind da tarefa anterior de modo a permitir que os parâmetros sejam passados de forma posicional, tornando possível dar bind em um parâmetro do meio:

  auto f = bind( foo, __, __, 34 );                   // guardou 34 para o terceiro parâmetro de foo
  auto g = f( __, 56 );                               // colocou 56 como segundo parâmetro de f, ou seja, equivale a bind( foo, __, 56, 34 )
  cout << g( 9 ) << endl;                             // chamou foo( 9, 56, 34 )
  Crie uma classe PlaceHolder e declare uma variável global "PlaceHolder __;" A princípio essa classe é vazia, mas se você achar conveniente pode declarar membros ou métodos.

  Note que é necessário tratar quando se marca lugar para os parâmetros do fim:

  auto f = bind( foo, 89, __, __ );  // É o mesmo que bind( foo, 89 )
  Ou seja, "__" como último parâmetros devem ser ignorados.

*/

#include <tuple>
#include <type_traits>
#include <functional>
#include <iostream>

template <typename F, typename ...Args1>
class Bind;

class PlaceHolder {};
PlaceHolder __;

// Creditos: https://stackoverflow.com/questions/17178075/how-do-i-reverse-the-order-of-element-types-in-a-tuple-type
// Adaptacao para reverter tupla
template<typename T, typename TT = typename std::remove_reference<T>::type, size_t... I>
auto reverse_impl(T&& t, std::index_sequence<I...>) -> std::tuple<typename std::tuple_element<sizeof...(I) - 1 - I, TT>::type...> {
    return std::make_tuple(std::get<sizeof...(I) - 1 - I>(std::forward<T>(t))...);
}

template<typename T, typename TT = typename std::remove_reference<T>::type>
auto reverse(T&& t) -> decltype(reverse_impl(std::forward<T>(t), std::make_index_sequence<std::tuple_size<TT>::value>())) {
    return reverse_impl(std::forward<T>(t), std::make_index_sequence<std::tuple_size<TT>::value>());
}


template <typename ...Args>
constexpr auto inicio(std::tuple<Args...> tupla) {
	// usar optional<T>::optional ?
    if constexpr ( sizeof...(Args) > 0 )
        return std::get<0>(tupla);
}


// Creditos: Ajuda de Leonardo Ventura pela sugestao do modelo para remocao de PlaceHolders do final
template <typename ...Args>
inline constexpr auto remove_place_holder( std::tuple<Args...> tupla ) {
    auto reverso = reverse(tupla);

    if constexpr ( std::is_same_v<PlaceHolder,decltype(inicio(reverso))> )
        return remove_place_holder( reverse(final(reverso)) );
    else 
        return tupla;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





// Creditos: https://stackoverflow.com/questions/47460072/how-can-i-bubble-last-element-in-the-variadic-templates?noredirect=1&lq=1
// Adaptacao para pegar apenas o ultimo elemento da tupla!!!
template <typename T, size_t... indices>
inline constexpr auto final_impl(T tupla, std::index_sequence<indices...>) {
    return std::tuple{ std::get<indices+1>(tupla)... };
}

template <typename ...Args>
inline constexpr auto final(std::tuple<Args...> tupla) {
    return final_impl(tupla, std::make_index_sequence<sizeof...(Args)-1>());
}

template<typename ...Args1, typename ...Args2>
auto substitui_place_holder( std::tuple<Args1...> args1, std::tuple<Args2...> args2 ) {
	// auto arg1_inicial = std::get<0>(args1);
	// auto arg2_inicial = std::get<0>(args2);

    if constexpr (sizeof...(Args1) == 0 && sizeof...(Args2) != 0) {
        return args2;
    } else if constexpr(sizeof...(Args1) != 0 && sizeof...(Args2) == 0) {
        return args1;
    } else if constexpr ( std::is_same_v< PlaceHolder, decltype(inicio(args1)) > ) {
        return std::tuple_cat( std::tuple{inicio(args2)}, substitui_place_holder( final(args1),final(args2) ) );
    } else {
        return std::tuple_cat( std::tuple{inicio(args1)}, substitui_place_holder( final(args1), args2 ) );
    }
    
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





template <typename F, typename ...Args1>
class Bind 
{
private:
    F f;
    std::tuple<Args1...> args1;

public:
    Bind( F f, Args1... args1 ): f(f), args1(args1...) {}
    Bind( F f, std::tuple<Args1...> args1 ): f(f), args1(args1) {}
  
    template <typename ...Args2>
    auto operator()( Args2... args2 ) {
		auto sph = substitui_place_holder( args1, std::tuple{args2...} );
		return resolve( sph );
    }
private:

	template <typename ...Args>
	auto resolve ( std::tuple<Args...> args ) {
	    if constexpr( std::is_invocable_v<F, Args...> )
	    	return std::apply( f, args );
	    else	
			return Bind<F,Args...>{ f, args };
	}


};


template <typename F, typename ...Args1>
auto bind( F f, std::tuple<Args1...> args1 ) {
	return Bind{ f, remove_place_holder(args1) };
}

template <typename F, typename ...Args1>
auto bind( F f, Args1... args1 ) {
	return Bind{ f, remove_place_holder(std::tuple{args1...}) };
}
