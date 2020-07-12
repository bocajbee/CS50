-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.


SELECT title  -- first query to get the movies Johnny Depp starred in
FROM people JOIN stars
ON people.id = stars.person_id
    JOIN movies
    ON movies.id = stars.movie_id
    WHERE name = 'Johnny Depp'
INTERSECT -- intersect these two queries, to find which results appear in both
SELECT title -- second query to get the movies Helena Bonham Carter starred in
FROM people JOIN stars
ON people.id = stars.person_id
    JOIN movies
    ON movies.id = stars.movie_id
    WHERE name = 'Helena Bonham Carter'
