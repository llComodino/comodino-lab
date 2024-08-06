import std::io;
import std::core::mem;

enum Type {
  INT,
  FLOAT
}

fn void* add(void *x, void *y, Type t) {
  void *tot = null;

  switch (t) {
    case INT:
      if ( (tot = (int*)mem::malloc((int*).sizeof * 2) ) == null ) {
        io::printf("Not enough mem");
        return null;
      }
      *(int*)tot = ( *(int*)x + *(int*)y );
      break;

    case FLOAT:
      if ( (tot = (float*)mem::malloc((float*).sizeof * 2) ) == null ) {
        io::printf("Not enough mem");
        return null;
      }
      *(float*)tot = ( *(float*)x + *(float*)y );
      break;
  }

  return tot;
}

fn void main(String[] args)
{
  int x_i = 1_950_000;
  int y_i = 2_050_000;

  float x_f = 1.325f;
  float y_f = 4.769f;

  int tot_i   = *(int*)   add((void*)&x_i, (void*)&y_i, INT);
  float tot_f = *(float*) add((void*)&x_f, (void*)&y_f, FLOAT);

  io::printf("tot_i: %d\ntot_f: %2.4f\n", tot_i, tot_f);
}
