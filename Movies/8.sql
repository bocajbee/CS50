-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
-- Your query should output a table with a single column for the name of each person.
-- You may assume that there is only one movie in the database with the title Toy Story.
-- the primary key between all 3 of the "stars", "people" and "movies" tables is "id"

SELECT name
FROM people
JOIN stars
ON people.id = stars.person_id
    JOIN movies
    ON movies.id = stars.movie_id
    WHERE title LIKE 'toy story';