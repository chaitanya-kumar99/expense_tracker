DROP TABLE IF EXISTS expenses;

CREATE TABLE expenses (
    id SERIAL PRIMARY KEY,
    amount INTEGER NOT NULL CHECK (amount > 0),
    description TEXT NOT NULL,
    date DATE NOT NULL DEFAULT CURRENT_DATE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_expenses_date ON expenses(date);

INSERT INTO expenses (amount, description) VALUES
    (500, 'Lunch at restaurant'),
    (100, 'Auto to office'),
    (1500, 'New shoes');