select ADDRESS from movies.STUDIO where name = "MGM";
select BIRTHDATE from movies.MOVIESTAR where name="Sandra Bullock";
select name from movies.MOVIESTAR where name=(select starname from movies.STARSIN where movietitle=(select title from movies.MOVIE where title like '%Empire%' and year=1980));
select name from movies.MOVIESTAR where gender="M" or address="Malibu";

