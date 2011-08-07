INCLUDE = -Iinclude
OBJS = src/readcsv.o src/norm.o

all: kmeans

clean:
	$(RM) kmeans $(OBJS)

kmeans: src/kmeans.c $(OBJS)
	$(CC) $(INCLUDE) -o $@ $+ 

.c.o:
	$(CC) $(INCLUDE) -o $@ -c $<
