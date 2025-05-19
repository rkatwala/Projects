
-- Drop the table if it already exists (for reruns)
DROP TABLE IF EXISTS CONCEPT_SYNONYMS;

-- Create the table
CREATE TABLE CONCEPT_SYNONYMS (
  concept_id INTEGER NOT NULL,
  STR        TEXT    NOT NULL
);

-- Sample synonyms for concept_id = 1
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (1, 'apple');
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (1, 'red apple');
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (1, 'malus domestica');

-- Sample synonyms for concept_id = 2
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (2, 'banana');
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (2, 'yellow banana');
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (2, 'musa');

-- Sample synonyms for concept_id = 3
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (3, 'orange');
INSERT INTO CONCEPT_SYNONYMS (concept_id, STR) VALUES (3, 'citrus sinensis');
