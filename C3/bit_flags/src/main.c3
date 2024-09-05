module bit_flags;
import std::io;

enum Flags : int ( int bitshift ) {
  GAY       = ( 1 << 0 ),
  NOT_GAY   = ( 1 << 1 ),
  SUPER_GAY = ( 1 << 2 )
}

fn void read_flags(int data, int flags) {
  if (flags & Flags.GAY.bitshift) io::printfn("GAY: %d", data * 2);
  if (flags & Flags.NOT_GAY.bitshift) flags ^= Flags.SUPER_GAY.bitshift;
  if (flags & Flags.SUPER_GAY.bitshift) io::printfn("SUPER GAY: %d", data / 2);

  return;
}

fn int main(String[] args) {
  int data = 6;

  read_flags(data, Flags.GAY.bitshift | Flags.SUPER_GAY.bitshift);
  read_flags(data, Flags.GAY.bitshift | Flags.NOT_GAY.bitshift | Flags.SUPER_GAY.bitshift);

  return 0;
}
