
all: kmeans

clean:
	$(RM) kmeans

kmeans: kmeans.c readcsv.c
	$(CC) $<
