Постановка задачи для конкретного варианта
1. Хранящуюся в файле базу данных загрузить в оперативную память компьютера и построить дерево поиска заданного типа, упорядочивающее данные сначала по первому полю, затем   по второму и т.д.
2. Провести поиск по ключу в построенном дереве поиска.  В качестве ключа использовать три буквы ФИО студента. (Например, ключ поиска для Сидорова Ивана Кузьмича – СИК). Из записей с одинаковым ключом сформировать очередь. Вывести содержимое очереди.
3. При выполнении задания главное внимание следует уделить эффективности применяемых алгоритмов, исключению всех лишних операций.
4. Операции, выражающие логически завершенные действия, рекомендуется оформлять в виде подпрограмм, грамотно выбирая между процедурами и функциями. Имена переменных и  подпрограмм, параметры подпрограмм, используемые языковые конструкции должны способствовать удобочитаемости программы.
5. Для сравнения символьных строк КАТЕГОРИЧЕСКИ НЕ РЕКОМЕНДУЕТСЯ пользоваться встроенными языковыми средствами и библиотечными функциями.



B - номер базы данных;
B = 4 ВАЖНО:(файл base4.dat)
C - вариант условия упорядочения для этой базы данных:
С = 2 - по названию улицы, номеру дома и ФИО, К = первые три буквы названия улицы;
S - метод сортировки:
S = 4 Цифpовая соpтиpовка
В качестве ключа для упоpядочения нужно взять всего по нескольку (обычно не менее тpех) байт из соответствующих полей. Файл базы данных загpужается в динамическую память в виде очеpеди. Затем очеpедь соpтиpуется цифpовым методом. Hа основе упоpядоченной очеpеди стpоится индексный массив.
D - тип дерева поиска.
D = 2 Двоичное Б-дерево.