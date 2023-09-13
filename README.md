# OOP_FTI_TASKS
Семестровые задачи для курса ООП кафедры ФТИ
## Блок первый: Шаблоны

### Сортировка (1 балл)
Реализовать сортировку, работающую за O(nlog(n)) с задаваемым компаратором. Примерный интерфейс:
```
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
### Метапрограммирование (1 балл)
На этапе компиляции вычислить первые N чисел Фибоначчи.

### Ultimate SQRT (2 балла)

Реализовать функцию ultimate_sqrt, которая позволяла бы вычислять квадратный корень из практически любого типа, который ей передан.
ultimate_sqrt будет представлять из шаблон функции с явной специализацией для таких типов как: ```vector<T>, list<T>, forward_list<T>, set<T>, unordered_set<T>, map<K,V>, unordered_map<K,V> ```. Для map и unordered_map вычисляем только по V.

Пример входных данных:

```
int i_value = 4;
double d_value = 9;
std::vector<double> vector_values= {16, 25};
```
Пример использования функции:
```
ultimate_sqrt(i_value);   // 2
ultimate_sqrt(d_value); // 3.0
ultimate_sqrt(vector_values); // {4.0, 5.0}
```
### Filter Iterator (2 балла)
boost::filter_iterator - интерфейс класса + примеры использования.

http://www.boost.org/doc/libs/1_55_0/libs/iterator/doc/filter_iterator.html

Задача:

Реализовать класс, аналогичный boost::filter_iterator - итерируется только по тем элементам, которые удовлетворяют заданным условию.

### Transform Iterator (2 балла)
boost::transform_iterator - интерфейс класса + примеры использования
https://www.boost.org/doc/libs/1_74_0/libs/iterator/doc/transform_iterator.html

Задача:

Реализовать класс, аналогичный boost::filter_iterator - адаптирует итератор, изменяя оператор*, чтобы применить объект функции к результату разыменования итератора и возврата результата.



### Integer Range (3 балла)
Реализовать класс Range который создает последовательность. С задаваемым началом, концом и шагом.
Пример использования:
```
for (int i : Range<int>(1, 10))
        std::cout << i << ' '; // 1 2 3 4 5 6 7 8 9
for (int i : Range<int>(10))
        std::cout << i << ' '; // 0 1 2 3 4 5 6 7 8 9
for (int i : Range<int>(1, 10, 3))
        std::cout << i << ' '; // 1 4 7
```

### Shuffle Iterator (4 балла)
Реализовать класс shuffle_range и соответствующий ему iterator, который позволяет обойти диапазон (набор) значений в случайном (перемешанном) порядке.
```
int a[] = {0, 4, 5, 2, 8, 1};
std::forward_list < int > b = { 0, 4, 5, 2, 8, 1 };
std::unordered_map < int, int > c = {
    { 0, 0 }, { 4, 0 }, { 5, 0 }, { 2, 0 }, { 8, 0 }, { 1, 0 }
};

auto shuffle_a = make_shuffle(a, a+6);
auto shuffle_b = make_shuffle(b.begin(), b.end());
auto shuffle_c = make_shuffle(c.begin(), c.end());

for (auto i : shuffle_a)
    std::cout << (*i) << " ";

std::cout << std::endl;

for (auto i : shuffle_c)
 std::cout << (*i).first << " " << (*i).second << std::endl;

```
### Сериализация и дессериализация (4 балла)
Реализовать фреймворк для бинарной сериализации и десериализации произвольных структур данных.
Поддерживаемые контейеры: std::string;
vector<T> для любого сериализуемого типа T;
map<K, V> для любых сериализуемых типов K, V;

