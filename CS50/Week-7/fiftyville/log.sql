-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To find out what crimes were reported at Humphrey Street
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street'; --Theft of the CS50 duck took place at
-- 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time –
--each of their interview transcripts mentions the bakery. |

-- To find out the structure of the interviews table
SELECT * FROM interviews LIMIT 1;

--To find out the interviews done that day (Check for number plates on parking lot between 10 am to 10:15 t0 10:25 am) 5P2BI95       |

--(Check  cameras and cash transactions on ATM at Legget Street between 6am and 10 am) (Check call records that are less than a minute
--between 10:15 and 10:25 am ) (Check flights that head to Paris)
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- Ruth: (EXIT car exits within 10 minutes 10:15 and 10:25) Eugene:(Thief withdrew money earlier in the morning) Yaymond:(Phone call made less than a minute,
--reveiver bought the tickets)

-- To check info on bakery security logs
SELECT * FROM bakery_security_logs LIMIT 3;

-- To get information on the number plates between  10:15 and 10:25 am
SELECT * FROM bakery_security_logs WHERE activity = "exit" AND hour = 10 AND minute BETWEEN 15 AND 25;

--Check the names agaist the license plates
 SELECT *
   ...> FROM people
   ...> JOIN bakery_security_logs
   ...> ON people.license_plate = bakery_security_logs.license_plate
   ...> WHERE bakery_security_logs.year = 2021
   ...>   AND bakery_security_logs.activity = "exit"
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25;

 -- To acquire the account numbers of all transations done earlier at Legget Street on the morning of the theft
SELECT * FROM atm_transactions WHERE day = 28 AND transaction_type = "withdraw"  AND  atm_location LIKE '%Legget%';

--check against people ID
SELECT *
   ...> FROM atm_transactions
   ...> JOIN bank_accounts
   ...> ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN people
   ...> ON people.id = bank_accounts.person_id
   ...> WHERE atm_transactions.day = 28
   ...> AND atm_transactions.transaction_type = "withdraw"
   ...> AND atm_transactions.atm_location LIKE '%Legget%';

-- To get phone records less than a minute
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;
--add name to call list

-- To get all info from people who made calls and received them on the day of the theft
SELECT * FROM people WHERE phone_number IN (SELECT phone_number FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60);

--Check names of everyone that called on suspect date
sqlite> SELECT p.name, pc.caller, pc.receiver, pc.year, pc.month, pc.day, pc.duration
   ...> FROM phone_calls pc
   ...> JOIN people p ON pc.caller = p.phone_number
   ...> WHERE pc.year = 2021 AND pc.month = 7 AND pc.day = 28 AND duration < 60;

-- To find the person ID of everyone that withdrew money
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND
transaction_type = "withdraw"  AND  atm_location LIKE '%Legget%');

-- To get passport numbers of everyone that made transactions on that day

 SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND transaction_type = 'withdraw' AND atm_location LIKE '%Legget%'));

--explore airports and get fiftyvile id
SELECT * FROM airports WHERE city = "Fiftyville"; -- id 8
-- To get info on flights taken on 29th
SELECT * FROM flights WHERE day = 29;
-- Earliest flight was at 8 am
--Flight ID to New Yor is 36
-- Check destination airport
SELECT full_name FROM airports WHERE id = 4;

-- To get flight info on all people that withdrew money on day of theft
SELECT flight_id FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_
number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND transaction_type = 'withdraw' AND atm_location LIKE '%Legget%')));

-- To get the flight id of the earliest flight
SELECT id FROM flights WHERE day = 29 AND hour = 8;

-- To get info on passengers who flew out of fiftville on the earliest flight
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND hour = 8);

--Find names of everyone who flew out of Fiftyville on the 8 am flight
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND hour = 8));

--passport numbers of everyone on the flight to New York

--Check all the conditions we've types and narrow down
SELECT name
   ...> FROM people
   ...> WHERE phone_number IN (
   ...>     SELECT phone_number
   ...>     FROM phone_calls
   ...>     WHERE month = 7 AND day = 28 AND duration < 60
   ...> )
   ...> AND passport_number IN (
   ...>     SELECT passport_number
   ...>     FROM passengers
   ...>     WHERE flight_id IN (
   ...>         SELECT id
   ...>         FROM flights
   ...>         WHERE day = 29 AND hour = 8
   ...>     )
   ...> )
   ...> AND id IN (
   ...>     SELECT person_id
   ...>     FROM bank_accounts
   ...>     WHERE account_number IN (
   ...>         SELECT account_number
   ...>         FROM atm_transactions
   ...>         WHERE day = 28 AND transaction_type = "withdraw" AND atm_location LIKE '%Legget%'
   ...>     )
   ...> )
   ...> AND license_plate IN (
   ...>     SELECT license_plate
   ...>     FROM bakery_security_logs
   ...>     WHERE year = 2021 AND activity = "exit" AND hour = 10 AND minute BETWEEN 15 AND 25
   ...> );

   -- narrow down from Bruce to Luca
    -- Bruce and Luca phone numbers
   SELECT phone_number FROM people WHERE name IN ('Bruce', 'Luca');

-- narrow down phone caller and reciever

SELECT name, phone_calls.receiver
      FROM people
      JOIN phone_calls ON people.phone_number = phone_calls.caller
      WHERE phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60
      AND people.name IN ('Bruce', 'Luca');


   --narrowed down to Bruce
SELECT name
   ...> FROM people
   ...> JOIN phone_calls ON people.phone_number = phone_calls.receiver
   ...> WHERE phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60;

   --get the acomplice by checking phonecall
   SELECT name FROM people WHERE phone_number = '(375) 555-8161';