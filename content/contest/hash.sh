# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed. CTRL+D to send EOF
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum | cut -c-6
