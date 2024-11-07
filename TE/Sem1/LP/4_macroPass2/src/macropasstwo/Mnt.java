package macropasstwo;

public class Mnt {
	  public String name;
	    public int addr;
	    public int arg_cnt;

	    public Mnt(String nm, int address) {
	        this.name = nm;
	        this.addr = address;
	        this.arg_cnt = 0;
	    }

	    public Mnt(String nm, int address, int total_arg) {
	        this.name = nm;
	        this.addr = address;
	        this.arg_cnt = total_arg;
	    }
}
