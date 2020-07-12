-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman
SELECT title FROM(
    SELECT DISTINCT people.id, name, title
    FROM people
    JOIN stars
    ON people.id = stars.person_id
        JOIN movies
        ON movies.id = stars.movie_id
            JOIN ratings
            ON ratings.movie_id = movies.id
            WHERE name = 'Chadwick Boseman'
            ORDER BY rating DESC
            LIMIT 5
);