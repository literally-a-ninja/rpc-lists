
/* 
 * list.x  Specification of the remote list manipulation server/client
 */ 
  
typedef double items<>; 	/* list items			*/

program LIST_MANI_PROG { 
    version DATE_VERS { 
        double	sum(items) = 1;	/* sum(list) return the sum of the numbers.     = 1 */ 
        double	max(items) = 2;	/* max(list) return the maximum of the numbers. = 2 */ 
        double	min(items) = 3;	/* min(list) return the minimum of the numbers. = 3 */ 
    } = 1;
} = 0x3CAFEDAD;	/* program number = 0x3CAFEDAD */ 
