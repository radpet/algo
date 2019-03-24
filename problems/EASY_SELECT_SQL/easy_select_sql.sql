select ADDRESS from movies.STUDIO where name = "MGM";
select BIRTHDATE from movies.MOVIESTAR where name="Sandra Bullock";
select name from movies.MOVIESTAR where name=(select starname from movies.STARSIN where movietitle=(select title from movies.MOVIE where title like '%Empire%' and year=1980));
select name from movies.MOVIESTAR where gender="M" or address="Malibu";

select model, speed, hd from pc.pc where price  <1200;
select model, 1.1*price as p from pc.laptop order by p;
select model, ram, screen from pc.laptop where price > 1000;
select model from pc.printer where color="y";
select model, speed, hd from pc.pc where (cd="12x" or cd="16x") and price<2000;
select code, model, speed+ram+10*screen as r from pc.laptop order by r

select class, country from ships.CLASSES where numguns < 10;
select name as shipName from ships.SHIPS where launched < 1918;
select ship,battle,result from ships.OUTCOMES where result="sunk";
select name from ships.SHIPS where name=class;
select name from ships.SHIPS where name like "R%";
select name from ships.SHIPS  where name like "% %" and name not like "% % %";
