-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
-- Your query should output a table with a single column for the name of each person.
-- People with the same birth year may be listed in any order.
-- No need to worry about people who have no birth year listed, so long as those who do have a birth year are listed in order.
-- If a person appeared in more than one movie in 2004, they should only appear in your results once.
-- https://www.w3schools.com/sql/sql_distinct.asp

SELECT name from(  -- nesting this will create a "3rd" temp table where we can selectivly choose to only print the "name" from the 2nd temp table a line below
    SELECT DISTINCT people.id, name --  create a 2nd temp table by selecting a distinct people.id + name from the 1st temp table created below, so there can still be people with the same name, as long as they have a different people_id
    FROM people -- take the first "people" table
    JOIN stars -- join it with the 'stars" table
    ON people.id = stars.person_id -- using "people,id" as the column to be the primary key and "stars.person_id" as the foriegn key
      JOIN movies -- then join/add the "movies" table to this 1st temp table
      ON movies.id = stars.movie_id -- by using "movies.id" as the primary key and "stars.movie_id" as the foriegn key
      WHERE year = 2004 and year IS NOT NULL  -- where the "year" colum in this 1st temp table is == 2004
      ORDER BY birth; -- also order every field in this 1st temp table by birth
);
