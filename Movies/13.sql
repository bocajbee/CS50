-- https://cs50.harvard.edu/x/2020/psets/7/movies/
-- write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.


SELECT name FROM(
	SELECT DISTINCT people.id, name
	FROM people JOIN stars
	ON people.id = stars.person_id
		WHERE name IS NOT 'Kevin Bacon' AND stars.movie_id IN( -- this checks for all of the movie_ids in stars that match with ALL of the movie.ids the inner nested query returned outside of its bubble below
		SELECT movies.id -- inner nested query, to get a list of movies Kevin Bacon was in, this inner nested query passes out the IDs of the movied Kbacon is in to be used as a reference above
		FROM people JOIN stars
		ON people.id = stars.person_id
		   JOIN movies
           ON movies.id = stars.movie_id
           WHERE name = 'Kevin Bacon' AND birth == 1958
))
