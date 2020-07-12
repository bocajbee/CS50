-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
-- Your query should output a table with two columns, one for the title of each movie and one for the rating of each movie.
-- Movies that do not have ratings should not be included in the result.
SELECT movies.title, ratings.rating
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id -- choose which column and row on each of the two tables we will join by and how we connect these two rows from each table
WHERE movies.year = 2010
ORDER BY ratings.rating DESC, movies.title;