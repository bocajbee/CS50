-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- In 1.sql, write a SQL query to list the titles of all movies released in 2008. Your query should output a table with a single column for the title of each movie.
SELECT title, COUNT(title) FROM movies WHERE year = 2008;