
--ユーザID、ユーザ名、パスワード
CREATE TABLE IF NOT EXISTS users (
    user_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_name TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
);
--教科ID、教科名
CREATE TABLE IF NOT EXISTS subjects (
    subject_id INTEGER PRIMARY KEY AUTOINCREMENT,
    subject_name TEXT NOT NULL
);
--試験ID、ユーザID、試験日
CREATE TABLE IF NOT EXISTS exam_data (
    exam_id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    exam_date DATE NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
);
--試験ID、ユーザID、教科ID、点数
CREATE TABLE IF NOT EXISTS exam_results (
    user_id INTEGER,
    exam_id INTEGER,
    subject_id INTEGER,
    score INTEGER,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (exam_id) REFERENCES exam_data(exam_id),
    FOREIGN KEY (subject_id) REFERENCES subjects(subject_id)
);
