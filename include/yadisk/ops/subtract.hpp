#ifndef SUBTRACT_HPP
#define SUBTRACT_HPP

#include "Resource.hpp"
#include "Predicate.hpp"
#include "Tree.hpp"

using yadisk::ops::Resource;
using yadisk::ops::Predicate;
using yadisk::ops::Tree;
/**
Выполняет сравнение хэш-функций по алгоритму SHA-256
\param[in] json одного дерева
\param[in] json другого дерева
\return true, если хэши совпадают, false в противном случае
**/
bool SHA256(const json& left, const json& right);
/**
Выполняет сравнение хэш-функций по алгоритму MD5
\param[in] json одного дерева
\param[in] json другого дерева
\return true, если хэши совпадают, false в противном случае
**/
bool MD5(const json& left, const json& right);

namespace Operations
{
	
/**
Выполняет вычитание двух деревьев
\param[in] первое дерево
\param[in] второе дерево
\param[in] предикат (true, если ресурсы совпадают; false в противном случае)
\return поддерево, являющееся результатом вычитания второго дерева из первого
\include examples/example.cpp
**/
	auto subtract(Tree tree1, Tree tree2, Predicate pred = SHA256) -> Tree&;
}

#endif
