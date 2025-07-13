DROP VIEW IF EXISTS route_display;

CREATE VIEW route_display AS
SELECT 
    b.route_id,
    d1.district_name AS from_district,
    d2.district_name AS to_district,
    b.departure_time,
    b.arrival_time
FROM routes AS b
JOIN districts AS d1 ON b.from_district = d1.districts_id
JOIN districts AS d2 ON b.to_district= d2.districts_id;
SELECT * FROM route_display;
INSERT INTO districts (district_name) VALUES ('Melamchi');
SELECT * FROM route_display LIMIT 1;
-- 1. Rename old table
ALTER TABLE routes RENAME TO routes_old;

-- 2. Recreate table with correct column name
CREATE TABLE routes (
    route_id INTEGER PRIMARY KEY AUTOINCREMENT,
    from_district INTEGER,
    to_district INTEGER, -- ✅ correct spelling
    departure_time INTEGER,
    arrival_time INTEGER,
    price INTEGER,
    bus_id INTEGER,
    FOREIGN KEY(from_district) REFERENCES districts(districts_id),
    FOREIGN KEY(to_district) REFERENCES districts(districts_id)
);

-- 3. Copy data over (if needed, fix column name manually before this)
INSERT INTO routes (route_id, from_district, to_district, departure_time, arrival_time, price, bus_id)
SELECT route_id, from_district, to_district, departure_time, arrival_time, price, bus_id
FROM routes_old;

-- 4. Drop old table
DROP TABLE routes_old;
DROP VIEW IF EXISTS route_display;

CREATE VIEW route_display AS
SELECT 
    b.route_id,
    d1.district_name AS from_district,
    d2.district_name AS to_district,
    b.departure_time,
    b.arrival_time
FROM routes AS b
JOIN districts AS d1 ON b.from_district = d1.districts_id
JOIN districts AS d2 ON b.to_district = d2.districts_id;
DROP VIEW IF EXISTS route_display;

CREATE VIEW route_display AS
SELECT 
    b.route_id,
    d1.district_name AS from_district,
    d2.district_name AS to_district,
    b.departure_time,
    b.arrival_time
FROM routes AS b
JOIN districts AS d1 ON b.from_district = d1.districts_id
JOIN districts AS d2 ON b.to_district = d2.districts_id;
SELECT * FROM route_display LIMIT 1;
PRAGMA table_info(route_display);
DROP VIEW IF EXISTS route_display;

CREATE VIEW route_display AS
SELECT 
    r.route_id,
    d1.district_name AS from_district,
    d2.district_name AS to_district,
    r.departure_time,
    r.arrival_time
FROM routes r
JOIN districts d1 ON r.from_district = d1.districts_id
JOIN districts d2 ON r.to_district = d2.districts_id;
SELECT * FROM route_display LIMIT 1;

	










