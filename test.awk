BEGIN {
	status = 0
	stderr = "/dev/stderr"
}

/^[^#]/ {
	if (NF != 3) {
		print "Error: " FILENAME ":" NR ": " $0 >> stderr
		exit 1
	}

	want = $3

	cmd = "./base " $1 " " $2
	cmd | getline got
	close(cmd)

	if (got != want) {
		print "Failure: " FILENAME ":" NR ": expected '" $3 "'; got '" out "'" >> stderr
		status = 1
	}
}

END {
	exit status
}
