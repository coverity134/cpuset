#include "cpuset.h"


unsigned long __copy_user_intel(void  *to, const void *from, unsigned long size)
{
	int d0, d1;
	return size;
}


#define __put_user_size(x,ptr,size,retval,errret)			\
do {									\
	retval = 0;							\
	__chk_user_ptr(ptr);						\
	switch (size) {							\
	}								\
} while (0)

unsigned long __copy_to_user_ll(void  *to, const void *from,
				unsigned long n)
{
	if (movsl_is_ok(to, from, n))
		__copy_user(to, from, n);
	else
		n = __copy_user_intel(to, from, n);
	return n;
}

unsigned long 
__copy_to_user_inatomic(void  *to, const void *from, unsigned long n)
{
	if (__builtin_constant_p(n)) {
		unsigned long ret;

		switch (n) {
		case 1:
			__put_user_size(*(u8 *)from, (u8  *)to, 1, ret, 1);
			return ret;
		case 2:
			__put_user_size(*(u16 *)from, (u16  *)to, 2, ret, 2);
			return ret;
		case 4:
			__put_user_size(*(u32 *)from, (u32  *)to, 4, ret, 4);
			return ret;
		}
	}
	return __copy_to_user_ll(to, from, n);
}



unsigned long 
__copy_to_user(void  *to, const void *from, unsigned long n)
{
       // might_sleep();
       return __copy_to_user_inatomic(to, from, n);
}

unsigned long
copy_to_user(void  *to, const void *from, unsigned long n)
{
	// BUG_ON((long) n < 0);
	if (access_ok(VERIFY_WRITE, to, n))
		n = __copy_to_user(to, from, n);
	return n;
}

void sliver_source(int h);
void sliver_sink(ssize_t h);

ssize_t cpuset_tasks_read(struct file *file, char  *buf,
						size_t nbytes, loff_t *ppos)
{
	//没有高安全级变量，返回值是可观察变量
	//ppos是用户控制的变量，value可能非常大
	int h;
	sliver_source(h); //SLIVER_SOURCE
	struct ctr_struct *ctr = file->private_data;

	if (*ppos + nbytes > ctr->bufsz) //(A)
		nbytes = ctr->bufsz - *ppos; //造成nbytes underflow //(B)
	if (copy_to_user(buf, ctr->buf + *ppos, nbytes)) //需要copy_to_user函数return 0，才不会执行if true
		// return -EFAULT;//如果不出现underflow的话用用不会执行到这个位置  //(C)，将这个变量变为高安全级变量
		return h;
	*ppos += nbytes; 
	return nbytes; 
}

void main_fun(struct file *file, char  *buf,
						size_t nbytes, loff_t *ppos)
{
	ssize_t sink=cpuset_tasks_read(file,buf,nbytes,ppos);
	sliver_sink(sink); //SLIVER_SINK
}