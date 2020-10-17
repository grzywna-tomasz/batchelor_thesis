static void fun1(void){
	char *cp = 0;
	
	*cp = '!';
}

int main(void){
	fun1();
	return 0;
}
