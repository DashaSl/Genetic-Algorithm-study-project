# Учебная практика по генетическим алгоритмам
Для работы программы требуется наличие библиотеки PyQt6
```
sudo apt install python3-pyqt6
sudo apt install python3-pyqtgraph
```
Чтобы скомпилировать код и запустить программу
```
make
python3 main.py
```

## Приближение ступенчатой функцией
Задание: для заданного полинома f(x) (степень не больше 8) необходимо найти параметры (высоты ступеней) ступенчатой функции g(x), которая приближает полиномиальную функцию. Т.е. минимизировать расстояние |f(x) - g(x)| между функциями на заданном интервале [l, r]. Количество и длина ступеней вводятся пользователем.


**Polynimial** - многочлен\
Поля:
  - coefficients - вектор коэффициентов многочлена
  - left - левая граница интервала, на котором определён многочлен
  - right - правая граница интервала\
Методы:
  - Инициализация (инициализируется вектором коэффициентов coefs)
  - getValue (получение значения многочлена)
  - evaluation (оценка разности функции и её апроксимации)
  - print()

**Chromosome** - класс хромосомы (индивида)
  Поля:
- double probMutation - вероятность мутации каждого гена
- int number - номер хромосомы
- std::vector<double> genes - вектор генов
- int length - длина хромосомы
- double max_mutation_step
- double down_border
- double up_border
- double estimate - оценка, насколько данная хромосома апроксимирует функцию.
  Методы:
  - Chromosome(double probMutation, double down, double up, int number, int len) - инициализация. Создает вектор рандомных высот длины N между down и up и записывает в поле genes
  - static std::vector<Chromosome> recombination(Chromosome parent1, Chromosome parent2, int method = 0)
  - void mutate(); - мутация
  - double new_gene(double old_gene);
  - static void discr_recomb(Chromosome parent1, Chromosome parent2, std::vector<Chromosome>& answer); - дискретная рекомбинация
  - void print_test();

**Population** - класс популяции
  Поля:
 - chromosomes - вектор индивидов.
 - countIndivids - количество хромосом
  Методы:
- Population() - инициализация. Создание вектора рандомных хромосом.
- updatePopulation - обновление хромосом
- elite_selection - Элитарная селекция

**Algorithm** - класс, в котором выполняется алгоритм 
  Поля:
- Population population - текущая популяция
- Polynomial polynom - полином
- int iteration - количество итераций (поколений)
- double criterion - критерий завершения 
  Методы
- void start(); - Запуск алгоритма




