-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0. Your query should output a table with a single column for the name of each person.
SELECT name FROM(
    SELECT DISTINCT people.id, people.name
    FROM people
    JOIN directors
    ON people.id = directors.person_id
        JOIN ratings
        ON ratings.movie_id = directors.movie_id
        WHERE rating >= 9.0
);