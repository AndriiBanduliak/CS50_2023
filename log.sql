-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Keep a log of any SQL queries you execute as you solve the mystery.

/* INFO
Theft took place on July 28th 2021
Theft took place on Humphrey Street */

/* GOAL
Who the thief is
What city the thief escaped to
Who the thief’s accomplice is who helped them escape */

-- Searching for all crime reports on Humphrey Street on July 28th 2021
SELECT description
    FROM crime_scene_reports
    WHERE street = "Humphrey Street"
    AND day = 28
    AND month = 7
    AND year = 2021;

/* Update:  Theft took place at 10:15am at the Humphrey Street bakery. Three witnesses – each of their interview transcripts mentions the bakery. */

-- Search for interviews on July 28th 2021 that mentions the bakery
SELECT name, transcript
    FROM interviews
    WHERE day = 28
    AND month = 7
    AND year = 2021
    AND transcript LIKE "%bakery%";

/* Update:  Witnesses:
            Ruth said the thief left the bakery sometime within ten minutes
            Eugene saw the thief by the ATM on Leggett Street withdrawing money earlier that morning
            Raymond heard the thief say they would catch a flight the next day, asked accomplice to purchase it */

-- Check all license plates that exited the bakery on 2021-07-28 between 10:15 and 10:25
SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2021
    AND activity = "exit"
    AND hour = 10
    AND minute BETWEEN 15 AND 25;

/* Update:  License plates that left the bakery between 10:15 and 10:25:
            5P2BI95
            94KL13X
            6P58WS2
            4328GD8
            G412CB7
            L93JTIZ
            322W7JE
            0NTHK55 */

-- Select the people who withdraw money on Leggett Street that morning intersected with the license plates
SELECT *
    FROM people
    WHERE id
        IN
            (SELECT person_id
            FROM bank_accounts
            WHERE account_number
                IN
                    (SELECT account_number
                    FROM atm_transactions
                    WHERE day = 28
                    AND month = 7
                    AND year = 2021
                    AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
                    )
            )
INTERSECT
SELECT *
    FROM people
    WHERE license_plate
        IN
            (SELECT license_plate
                FROM bakery_security_logs
                WHERE day = 28
                AND month = 7
                AND year = 2021
                AND activity = "exit"
                AND hour = 10
                AND minute BETWEEN 15 AND 25);

/* Update:  Suspects:
            +--------+-------+----------------+-----------------+---------------+
            |   id   | name  |  phone_number  | passport_number | license_plate |
            +--------+-------+----------------+-----------------+---------------+
            | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
            | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
            | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
            | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
            +--------+-------+----------------+-----------------+---------------+ */

-- From the suspects list, check who caught the earliest flight on 2021-07-29 departuring from Fiftyville
SELECT *
    FROM passengers
    JOIN flights
        ON passengers.flight_id = flights.id
    JOIN people
        ON passengers.passport_number = people.passport_number
    WHERE flights.origin_airport_id =
            (SELECT id
            FROM airports
            WHERE city = "Fiftyville"
            )
    AND flights.day = 29
    AND flights.month = 7
    AND flights.year = 2021
    AND passengers.passport_number
        IN ("7049073643", "8496433585", "3592750733", "5773159633");


/* Update:  There are 3 results but only 2 suspects on the earliest flight:
            +--------+-------+----------------+-----------------+---------------+
            |   id   | name  |  phone_number  | passport_number | license_plate |
            +--------+-------+----------------+-----------------+---------------+
            | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
            | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
            +--------+-------+----------------+-----------------+---------------+ */

-- Check if they called someone that day
SELECT *
    FROM phone_calls
    WHERE caller
        IN ("(389) 555-5198", "(367) 555-5533")
    AND day = 28
    AND month = 7
    AND year = 2021
    AND duration < 60;

/* Update:  Narrowed it down to Bruce as the thief, and receiver is their accomplice
            +-----+----------------+----------------+------+-------+-----+----------+
            | id  |     caller     |    receiver    | year | month | day | duration |
            +-----+----------------+----------------+------+-------+-----+----------+
            | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
            +-----+----------------+----------------+------+-------+-----+----------+*/

-- Check who is the accomplice (person Bruce called)
SELECT *
    FROM people
    WHERE phone_number = "(375) 555-8161";

/* Update: The accomplice returned is Robin */


-- Check where the flight Bruce caught was headed:
SELECT city
    FROM airports
    WHERE id =
        (SELECT destination_airport_id FROM flights WHERE id = 36);

/* Update: Bruce flew to New York City */