-- 初期データ投入（DML）
INSERT OR IGNORE INTO users (username, password, email) VALUES
  ('alice', 'password1', 'alice@example.com'),
  ('bob',   'password2', 'bob@example.com');