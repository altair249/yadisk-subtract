#pragma once
using yadisk::ops::Resource;
using yadisk::ops::Predicate;
using yadisk::ops::Tree;

Tree subtract(Tree tree1, Tree tree2, Predicate pred = Hash);