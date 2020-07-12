-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- In 1.sql, write a SQL query to list the titles of all movies released in 2008. Your query should output a table with a single column for the title of each movie.
-- write a SQL query to determine the average rating of all movies released in 2012. Your query should output a table with a single column and a single row (plus optional header) containing the average rating.
SELECT avg(ratings.rating) -- select the avgerage of the ratings
FROM movies -- left table
INNER JOIN ratings  -- right table
ON movies.id = ratings.movie_id; -- choose which column and row on each of the two tables we will join by and how we connect these two rows from each table