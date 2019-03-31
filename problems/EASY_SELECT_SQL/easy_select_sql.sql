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

select starname from movies.STARSIN where movies.STARSIN.MOVIETITLE="Terms of Endearment";
select starname from movies.STARSIN where  movies.STARSIN.MOVIETITLE= (select title from movies.MOVIE where movies.MOVIE.STUDIONAME='MGM' and movies.MOVIE.YEAR=1995);
select starname from movies.STARSIN join movies.MOVIE on movies.STARSIN.MOVIETITLE=movies.MOVIE.TITLE where movies.MOVIE.STUDIONAME='MGM' and movies.MOVIE.YEAR=1995


select distinct MOVIE.TITLE, MOVIE.YEAR from MOVIE join STARSIN on MOVIE.TITLE=STARSIN.MOVIETITLE where MOVIE.YEAR < 1982 and not ( STARSIN.STARNAME like "%b%" or STARSIN.STARNAME like "%k%") order by MOVIE.YEAR;

select MOVIE.TITLE, MOVIE.LENGTH/60 from MOVIE where
 MOVIE.YEAR= (select MOVIE.YEAR from MOVIE where MOVIE.TITLE = "Terms of Endearment")
 and (  MOVIE.LENGTH <  (select MOVIE.LENGTH from MOVIE where MOVIE.TITLE = "Terms of Endearment") or MOVIE.LENGTH IS NULL);

select t.n, t.cnt from (select STARSIN.STARNAME as n , count(STARSIN.MOVIETITLE) as cnt  from STARSIN join MOVIE on STARSIN.MOVIETITLE=MOVIE.TITLE where MOVIE.YEAR > 1990 group by STARSIN.STARNAME) as t where t.cnt > 3;

select t.NAME, sum(t.res) as total_dmg from
(select *,IF( OUTCOMES.BATTLE IS NULL OR OUTCOMES.RESULT = 'ok', 0, count(*)) as res from SHIPS left join OUTCOMES on SHIPS.NAME=OUTCOMES.SHIP group by OUTCOMES.SHIP, OUTCOMES.RESULT
) as t group by t.NAME order by total_dmg desc;

select t.NAME, t.cnt from (select SHIPS.NAME, count(SHIPS.CLASS) as cnt from ships.SHIPS group by SHIPS.CLASS) as t where t.cnt > 3 and t.NAME in
(select OUTCOMES.SHIP from ships.OUTCOMES where OUTCOMES.RESULT='ok');

select t2.NAME, count(*) from ships.OUTCOMES join
(select t.NAME, t.cnt from (select SHIPS.NAME, count(SHIPS.CLASS) as cnt from ships.SHIPS group by SHIPS.CLASS) as t where t.cnt > 3) as t2
on OUTCOMES.SHIP=t2.NAME  where OUTCOMES.RESULT='ok' ;
