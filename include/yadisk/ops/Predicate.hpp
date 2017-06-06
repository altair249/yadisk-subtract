#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include "yadisk/ops/Resource.hpp"
using yadisk::ops::Resource;

namespace yadisk
{
	namespace ops
	{
		typedef std::function<bool(json, json)> Predicate;
	}
}

#endif
