CREATE TABLE IF NOT EXISTS "Translation" (
	"Key" TEXT NOT NULL,
	"Value" TEXT NOT NULL,
	"Locale" TExt NOT NULL,
	PRIMARY KEY("Key", "Locale")
);