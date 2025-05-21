-- students テーブル
CREATE TABLE IF NOT EXISTS students(
	student_id INTEGER PRIMARY KEY AUTOINCREMENT,
	name	TEXT	NOT NULL
);

-- subjects テーブル
CREATE TABLE IF NOT EXISTS subjects(
	subject_id INTEGER PRIMARY KEY AUTOINCREMENT,
	subject_name TEXT NOT NULL
);

-- exam_results テーブル
CREATE TABLE IF NOT EXISTS exam_results(
	exam_id INTEGER PRIMARY KEY AUTOINCREMENT,
	student_id INTEGER NOT NULL,
	subject_id INTEGER NOT NULL,
	exam_date TEXT NOT NULL,
	score INTEGER NOT NULL,
	FOREIGN KEY(student_id) REFERENCES students(student_id),
	FOREIGN KEY(subject_id) REFERENCES subjects(subject_id)
);

-- 
CREATE TABLE IF NOT EXISTS users(
	user_id INTEGER PRIMARY KEY AUTOINCREMENT,
	username TEXT UNIQUE NOT NULL,
	password TEXT NOT NULL
);

--
INSERT OR IGNORE INTO subjects (subject_name) VALUES
('国語'),('数学'),('英語'),('日本史'),('世界史'),('地理'),('化学'),('生物');
INSERT OR IGNORE INTO users (username, password) VALUES ('admin','admin123');