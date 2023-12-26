#pragma once

template<typename ...Types>
struct type_list
{
	template<template<typename...> typename Holder>
	using apply = Holder<Types...>;
};