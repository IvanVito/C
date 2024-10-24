# Разработка утилит cat и grep на С

## Введение

В рамках данного проекта была разработана реализация двух основных утилит Bash: `cat` и `grep`, написанных на языке программирования Си. Эти утилиты являются основными инструментами для работы с текстом в терминале Linux. Цель проекта заключалась в создании этих утилит, соответствующих стандартам и функционалу оригинальных утилит Bash, с акцентом на структурное программирование и поддержку всех необходимых опций.

### Информация об утилитах

#### Утилита `cat`

Команда `cat` используется для отображения, объединения и создания текстовых файлов. Основные опции утилиты:

| № | Опция  | Описание                                                   |
|---|--------|------------------------------------------------------------|
| 1 | -b     | Нумерует только непустые строки.                           |
| 2 | -e     | Отображает символы конца строки как `$`, предполагает опцию `-v`. |
| 3 | -n     | Нумерует все выходные строки.                              |
| 4 | -s     | Сжимает несколько смежных пустых строк.                    |
| 5 | -t     | Отображает табы как `^I`, предполагает опцию `-v`.          |

#### Утилита `grep`

Команда `grep` используется для поиска строк, соответствующих заданному шаблону. Основные опции утилиты:

| № | Опция  | Описание                                                   |
|---|--------|------------------------------------------------------------|
| 1 | -e     | Указывает шаблон для поиска.                               |
| 2 | -i     | Игнорирует различия регистра.                             |
| 3 | -v     | Инвертирует смысл поиска соответствий.                     |
| 4 | -c     | Выводит только количество совпадающих строк.               |
| 5 | -l     | Выводит только имена файлов, содержащих совпадения.        |
| 6 | -n     | Предваряет каждую строку номера строки из файла ввода.      |
| 7 | -h     | Выводит совпадающие строки без имен файлов.                |
| 8 | -s     | Подавляет сообщения об ошибках для несуществующих или нечитаемых файлов. |
| 9 | -f     | Получает регулярные выражения из файла.                    |
| 10| -o     | Печатает только совпадающие части строк.                   |

## Разработка утилиты `cat`

- **Разработка:** Утилита `cat` была разработана с поддержкой всех указанных флагов.
- **Расположение:** Исходные, заголовочные и сборочные файлы размещены в директории `src/cat/`.
- **Исполняемый файл:** Итоговый исполняемый файл назван `s21_cat` и после сборки будет находиться в директории `src/cat/`.

## Разработка утилиты `grep`

- **Разработка:** Утилита `grep` была реализована с поддержкой флагов: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`. Регулярные выражения обрабатывались с использованием библиотеки `regex`.
- **Расположение:** Исходные, заголовочные и сборочные файлы размещены в директории `src/grep/`.
- **Исполняемый файл:** Итоговый исполняемый файл назван `s21_grep`и после сборки будет находиться  в директории `src/grep/`.

### Часть 3: Дополнительно - Реализация дополнительных флагов для `grep`

- **Разработка:** Дополнительно реализованы флаги `-h`, `-s`, `-f`, `-o`.
- **Расположение:** Исходные, заголовочные и сборочные файлы размещены в директории `src/grep/`.


### Часть 4: Дополнительно - Реализация комбинаций флагов для `grep`

- **Разработка:** Реализованы парные комбинации флагов, например `-iv`, `-in`.
- **Расположение:** Исходные, заголовочные и сборочные файлы находятся в директории `src/grep/`.


## Заключение

Проект успешно завершен с реализацией утилит `cat` и `grep` в соответствии с требованиями. Утилиты поддерживают широкий спектр опций, соответствующих оригинальным утилитам Bash, с полным покрытием интеграционными тестами. Разработанные утилиты демонстрируют высокое качество кода и функциональность, соответствующую стандартам структурного программирования.
