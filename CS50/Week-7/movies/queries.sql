SELECT title FROM movies WHERE year = 2008;


SELECT birth FROM people WHERE name = "Emma Stone";


SELECT title FROM movies WHERE year >= 2018 ORDER BY title ASC;


SELECT COUNT(*) FROM ratings WHERE rating = 10.0;


SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year ASC;


SELECT AVG(rating) FROM ratings WHERE movie_id IN(SELECT id FROM movies WHERE year = 2012);


SELECT movies.title, ratings.rating FROM ratings JOIN movies ON ratings.movie_id = movies.id WHERE movies.year = 2010 ORDER BY rating DESC, movies.title ASC;


SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id =(SELECT id FROM movies WHERE title = "Toy Story"));


SELECT DISTINCT name -- Ensures name only appears once
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;



SELECT DISTINCT people.name
FROM people
JOIN directors ON directors.person_id = people.id
JOIN movies ON movies.id = directors.movie_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE rating >= 9.0;


SELECT movies.title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;



SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Bradley Cooper"
   OR people.name = "Jennifer Lawrence"

GROUP BY movies.title
HAVING COUNT(DISTINCT people.name) = 2;



SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN movies m ON m.id = s.movie_id
WHERE m.id IN (
    SELECT m.id FROM movies m
    JOIN stars s ON m.id = s.movie_id
    JOIN people p ON s.person_id = p.id
    WHERE p.name = "Kevin Bacon" AND p.birth = 1958
) AND p.name != "Kevin Bacon";





