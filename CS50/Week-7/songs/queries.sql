SELECT name FROM songs;
SELECT name FROM songs GROUP BY tempo;
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;
SELECT AVG(energy) AS average_energy FROM songs;
SELECT name FROM songs WHERE artist_id =(SELECT id FROM artists WHERE name = "Post Malone");
SELECT AVG(energy) AS average_energy FROM songs WHERE artist_id =(SELECT id FROM artists WHERE name = "Drake");
SELECT name FROM songs WHERE name LIKE '%feat%';