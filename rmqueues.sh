ipcs -q | awk '{ print $2; }' | egrep -v "Queues|ID" | egrep "[0-9]+" | xargs ipcrm -q
