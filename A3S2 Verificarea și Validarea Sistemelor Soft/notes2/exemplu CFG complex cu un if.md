[[CFG; control flow graph; graful fluxului de control]]

```c
FILE *fptr1, *fptr2, *fptr3;

int openfiles() {
	int i = 0;
	if(
		((( fptr1 = fopen("file1", "r")) != NULL) && (i++)
		                                         && (0)) ||
		((( fptr2 = fopen("file2", "r")) != NULL) && (i++)
		                                          && (0)) ||
		((( fptr3 = fopen("file2", "r")) != NULL) && (i++))
	);
	return i;
}
```

![[Pasted image 20240527091910.png]]