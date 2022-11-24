public class B {
    int a=1;
 
    int f(int b){
        a=b;
        return a;
    }
 
//    主类，java应用程序总是从主类的main方法开始执行
    public static void main(String []args){
       B b=new B();
        System.out.println(b.f(3));
    }
}