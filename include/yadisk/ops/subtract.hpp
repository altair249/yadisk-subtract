#ifndef SUBTRACT_HPP
#define SUBTRACT_HPP

#include "Resource.hpp"
#include "Predicate.hpp"
#include "Tree.hpp"

using yadisk::ops::Resource;
using yadisk::ops::Predicate;
using yadisk::ops::Tree;

bool SHA256(const json& left, const json& right);

bool MD5(const json& left, const json& right);

namespace Operations
{
	auto subtract(Tree tree1, Tree tree2, Predicate pred = SHA256) -> Tree&;
}

#endif
