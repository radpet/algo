<>
Упражнение 3 - Genetic Algorithms
В компютърна игра главният герой има събрани 5000 жълтици. Попада в пещера, където
среща търговец на артефакти. Търговецът продава N на брой различни артефакта (магически
лък за точна стрелба, бързи ботуши, и тн). Всеки артефакт има цена в жълтици и стойност
колко важен е за героя. Да се намерят предметите, които героя трябва да купи според
таблицата по-долу:
𝑣𝑖 − 𝑣𝑎𝑙𝑢𝑒 за героя
𝑤𝑖 − цена на артефакта
𝑥𝑖 ∈ {0,1} − купен или не е артефактът
max Sum(vi*xi)
sum(wi*xi) <=5000


N Item цена - wi value - vi
1 map 100 150
2 compass 120 40
3 Magic water 1600 200
4 Magic boots 700 160
5 Magic Bow 150 60
6 Flying carpet 680 45
7 Magic Ring 270 60
8 Magic Glasses 385 48
9 Life elixir 230 30
10 Magic animal 520 10
11 Sword 1700 400
12 Shield 500 300
13 Teleport 240 15
14 Magic berries 480 10
15 Magic umbrella 730 40
16 flower 420 70
17 Knife 430 75
18 Tent 220 80
19 Garlic 70 20
20 Silver Elixir 180 12
21 Magic Hat 40 50
22 magic beer 300 10
23 Silver Arrows 900 20
24 Mystic Orb 2000 150