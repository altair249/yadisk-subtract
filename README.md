# yadisk-subtract

[![Build Status](https://travis-ci.org/yadisk-ops/yadisk-subtract.svg?branch=master)](https://travis-ci.org/yadisk-ops/yadisk-subtract)

Данный репозиторий содержит часть проекта Yadisk-Operations, посвященную методу *subtract*.

## Получение разницы слепков двух дисков 
Задача заключается в реализации пакета **yadisk-subtract**, который содержит библиотеку, предоставляющую следующий интерфейс:

using yadisk::ops::Resource;
using yadisk::ops::Predicate;
using yadisk::ops::Tree;
 
namespace Operations {
  Tree subtract(Tree tree1, Tree tree2, Predicate pred = Hash);
}


Функция **subtract** возвращает разницу слепков tree1 и tree2.

## Сборка

Сборка проекта осуществляется с помощью утилиты для автоматической сборки CMake.
Пакетирование осуществляется с помощью утилиты CPack.
