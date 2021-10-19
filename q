BLKID(8)                     System Administration                    BLKID(8)

NNAAMMEE
       blkid - locate/print block device attributes

SSYYNNOOPPSSIISS
       bbllkkiidd  ----llaabbeell _l_a_b_e_l | ----uuuuiidd _u_u_i_d

       bbllkkiidd  [----nnoo--eennccooddiinngg  ----ggaarrbbaaggee--ccoolllleecctt  ----lliisstt--oonnee ----ccaacchhee--ffiillee _f_i_l_e]
              [----oouuttppuutt _f_o_r_m_a_t] [----mmaattcchh--ttaagg _t_a_g]  [----mmaattcchh--ttookkeenn  _N_A_M_E_=_v_a_l_u_e]
              [_d_e_v_i_c_e ...]

       bbllkkiidd  ----pprroobbee   [----ooffffsseett  _o_f_f_s_e_t]  [----oouuttppuutt  _f_o_r_m_a_t]  [----ssiizzee  _s_i_z_e]
              [----mmaattcchh--ttaagg _t_a_g] [----mmaattcchh--ttyyppeess _l_i_s_t]  [----uussaaggeess  _l_i_s_t]  _d_e_v_i_c_e
              ...

       bbllkkiidd  ----iinnffoo [----oouuttppuutt _f_o_r_m_a_t] [----mmaattcchh--ttaagg _t_a_g] _d_e_v_i_c_e ...

DDEESSCCRRIIPPTTIIOONN
       The  bbllkkiidd  program  is  the command-line interface to working with the
       lliibbbbllkkiidd(3) library.  It  can  determine  the  type  of  content  (e.g.
       filesystem  or swap) that a block device holds, and also the attributes
       (tokens, NAME=value pairs) from the content  metadata  (e.g.  LABEL  or
       UUID fields).

       IItt  iiss  rreeccoommmmeennddeedd  ttoo  uussee  llssbbllkk(8) ccoommmmaanndd ttoo ggeett iinnffoorrmmaattiioonn aabboouutt
       bblloocckk ddeevviicceess rraatthheerr tthhaann bbllkkiidd..  llssbbllkk(8) provides  more  information,
       better  control  on output formatting and it does not require root per‐
       missions to get actual information.

       When _d_e_v_i_c_e is specified, tokens from only this device  are  displayed.
       It  is  possible  to  specify  multiple _d_e_v_i_c_e arguments on the command
       line.  If none is given, all devices which appear  in  _/_p_r_o_c_/_p_a_r_t_i_t_i_o_n_s
       are shown, if they are recognized.

       Note  that  bbllkkiidd  reads information directly from devices and for non-
       root users it returns cached unverified information.  It is  better  to
       use  llssbbllkk  ----ffss  to  get  a  user-friendly overview of filesystems and
       devices.  llssbbllkk(8) is also easy to use in  scripts.   bbllkkiidd  is  mostly
       designed for system services and to test libblkid functionality.

       bbllkkiidd  has  two  main forms of operation: either searching for a device
       with a specific NAME=value pair, or displaying NAME=value pairs for one
       or more specified devices.

OOPPTTIIOONNSS
       The  _s_i_z_e  and  _o_f_f_s_e_t  arguments may be followed by the multiplicative
       suffixes like KiB (=1024), MiB (=1024*1024), and so on  for  GiB,  TiB,
       PiB,  EiB,  ZiB  and  YiB  (the "iB" is optional, e.g. "K" has the same
       meaning as "KiB"), or the suffixes KB (=1000), MB (=1000*1000), and  so
       on for GB, TB, PB, EB, ZB and YB.

       --cc, ----ccaacchhee--ffiillee _c_a_c_h_e_f_i_l_e
              Read  from  _c_a_c_h_e_f_i_l_e  instead of reading from the default cache
              file (see the CONFIGURATION FILE section for more details).   If
              you  want to start with a clean cache (i.e. don't report devices
              previously scanned but not necessarily available at this  time),
              specify _/_d_e_v_/_n_u_l_l.

       --dd, ----nnoo--eennccooddiinngg
              Don't  encode non-printing characters.  The non-printing charac‐
              ters are encoded by ^ and M- notation by default.  Note that the
              ----oouuttppuutt uuddeevv output format uses a different encoding which can‐
              not be disabled.

       --gg, ----ggaarrbbaaggee--ccoolllleecctt
              Perform a garbage collection pass on the blkid cache  to  remove
              devices which no longer exist.

       --hh, ----hheellpp
              Display a usage message and exit.

       --ii, ----iinnffoo
              Display  information  about  I/O Limits (aka I/O topology).  The
              'export' output format is automatically  enabled.   This  option
              can be used together with the ----pprroobbee option.

       --kk, ----lliisstt--ffiilleessyysstteemmss
              List all known filesystems and RAIDs and exit.

       --ll, ----lliisstt--oonnee
              Look up only one device that matches the search parameter speci‐
              fied with the  ----mmaattcchh--ttookkeenn  option.   If  there  are  multiple
              devices  that  match  the  specified  search parameter, then the
              device with the highest priority is returned, and/or  the  first
              device  found  at  a  given  priority.  Device types in order of
              decreasing priority are:  Device  Mapper,  EVMS,  LVM,  MD,  and
              finally regular block devices.  If this option is not specified,
              bbllkkiidd will print all of the devices that match the search param‐
              eter.

       --LL, ----llaabbeell _l_a_b_e_l
              Look  up  the  device  that  uses this filesystem _l_a_b_e_l; this is
              equal to ----lliisstt--oonnee ----oouuttppuutt ddeevviiccee  ----mmaattcchh--ttookkeenn  LLAABBEELL==_l_a_b_e_l.
              This  lookup  method  is able to reliably use /dev/disk/by-label
              udev symlinks  (dependent  on  a  setting  in  /etc/blkid.conf).
              Avoid using the symlinks directly; it is not reliable to use the
              symlinks without verification.  The ----llaabbeell option works on sys‐
              tems with and without udev.

              Unfortunately,  the original bbllkkiidd(8) from e2fsprogs uses the --LL
              option as a synonym for --oo lliisstt.  For better portability, use --ll
              --oo ddeevviiccee --tt LLAABBEELL==_l_a_b_e_l and --oo lliisstt in your scripts rather than
              the --LL option.

       --nn, ----mmaattcchh--ttyyppeess _l_i_s_t
              Restrict the probing functions  to  the  specified  (comma-sepa‐
              rated)  _l_i_s_t of superblock types (names).  The list items may be
              prefixed with "no" to specify the types which should be ignored.
              For example:

                blkid --probe --match-types vfat,ext3,ext4 /dev/sda1

              probes for vfat, ext3 and ext4 filesystems, and

                blkid --probe --match-types nominix /dev/sda1

              probes for all supported formats except minix filesystems.  This
              option is only useful together with ----pprroobbee.

       --oo, ----oouuttppuutt _f_o_r_m_a_t
              Use the specified output format.  Note that the order  of  vari‐
              ables and devices is not fixed.  See also option --ss.  The _f_o_r_m_a_t
              parameter may be:

              ffuullll   print all tags (the default)

              vvaalluuee  print the value of the tags

              lliisstt   print the devices in a user-friendly format; this  output
                     format  is  unsupported for low-level probing (----pprroobbee or
                     ----iinnffoo).

                     This  output  format  is  DDEEPPRREECCAATTEEDD  in  favour  of  the
                     llssbbllkk(8) command.

              ddeevviiccee print  the device name only; this output format is always
                     enabled for the ----llaabbeell and ----uuuuiidd options

              uuddeevv   print key="value" pairs for easy  import  into  the  udev
                     environment;  the keys are prefixed by ID_FS_ or ID_PART_
                     prefixes

                     The udev output returns the ID_FS_AMBIVALENT tag if  more
                     superblocks  are  detected,  and ID_PART_ENTRY_* tags are
                     always returned for all partitions including empty parti‐
                     tions.  This output format is DDEEPPRREECCAATTEEDD.

              eexxppoorrtt print  key=value  pairs for easy import into the environ‐
                     ment; this output format is  automatically  enabled  when
                     I/O Limits (----iinnffoo option) are requested.

                     The non-printing characters are encoded by ^ and M- nota‐
                     tion and all potentially unsafe characters are escaped.

       --OO, ----ooffffsseett _o_f_f_s_e_t
              Probe at the given _o_f_f_s_e_t  (only  useful  with  ----pprroobbee).   This
              option can be used together with the ----iinnffoo option.

       --pp, ----pprroobbee
              Switch  to  low-level  superblock  probing  mode  (bypassing the
              cache).

              Note that low-level probing also returns information about  par‐
              tition  table  type  (PTTYPE  tag)  and partitions (PART_ENTRY_*
              tags). The tag names produced by low-level probing are based  on
              names  used  internally by libblkid and it may be different than
              when executed without ----pprroobbee (for example  PART_ENTRY_UUID=  vs
              PARTUUID=).

       --ss, ----mmaattcchh--ttaagg _t_a_g
              For  each (specified) device, show only the tags that match _t_a_g.
              It is possible to specify multiple ----mmaattcchh--ttaagg options.   If  no
              tag  is specified, then all tokens are shown for all (specified)
              devices.  In order to just refresh the cache without showing any
              tokens, use ----mmaattcchh--ttaagg nnoonnee with no other options.

       --SS, ----ssiizzee _s_i_z_e
              Override the size of device/file (only useful with ----pprroobbee).

       --tt, ----mmaattcchh--ttookkeenn _N_A_M_E_=_v_a_l_u_e
              Search  for  block  devices with tokens named _N_A_M_E that have the
              value _v_a_l_u_e, and display any devices which  are  found.   Common
              values  for _N_A_M_E include TTYYPPEE, LLAABBEELL, and UUUUIIDD.  If there are no
              devices specified on the command line, all block devices will be
              searched; otherwise only the specified devices are searched.

       --uu, ----uussaaggeess _l_i_s_t
              Restrict  the  probing  functions  to the specified (comma-sepa‐
              rated) _l_i_s_t  of  "usage"  types.   Supported  usage  types  are:
              filesystem,  raid, crypto and other.  The list items may be pre‐
              fixed with "no" to specify  the  usage  types  which  should  be
              ignored.  For example:

                blkid --probe --usages filesystem,other /dev/sda1

              probes for all filesystem and other (e.g. swap) formats, and

                blkid --probe --usages noraid /dev/sda1

              probes  for  all supported formats except RAIDs.  This option is
              only useful together with ----pprroobbee.

       --UU, ----uuuuiidd _u_u_i_d
              Look up the device that uses this  filesystem  _u_u_i_d.   For  more
              details see the ----llaabbeell option.

       --VV, ----vveerrssiioonn
              Display version number and exit.

RREETTUURRNN CCOODDEE
       If  the specified device or device addressed by specified token (option
       ----mmaattcchh--ttookkeenn) was found and it's possible to  gather  any  information
       about  the  device,  an  exit  code  0  is  returned.   Note the option
       ----mmaattcchh--ttaagg filters output tags, but it does not affect return code.

       If the specified token was not found, or no (specified)  devices  could
       be identified, an exit code of 2 is returned.

       For usage or other errors, an exit code of 4 is returned.

       If an ambivalent low-level probing result was detected, an exit code of
       8 is returned.

CCOONNFFIIGGUURRAATTIIOONN FFIILLEE
       The standard location of the _/_e_t_c_/_b_l_k_i_d_._c_o_n_f config file can  be  over‐
       ridden  by  the environment variable BLKID_CONF.  The following options
       control the libblkid library:

       _S_E_N_D___U_E_V_E_N_T_=_<_y_e_s_|_n_o_t_>
              Sends uevent when  _/_d_e_v_/_d_i_s_k_/_b_y_-_{_l_a_b_e_l_,_u_u_i_d_,_p_a_r_t_u_u_i_d_,_p_a_r_t_l_a_b_e_l_}_/
              symlink  does  not match with LABEL, UUID, PARTUUID or PARTLABEL
              on the device.  Default is "yes".

       _C_A_C_H_E___F_I_L_E_=_<_p_a_t_h_>
              Overrides the standard location of the cache file.  This setting
              can  be  overridden  by  the  environment  variable  BLKID_FILE.
              Default is _/_r_u_n_/_b_l_k_i_d_/_b_l_k_i_d_._t_a_b, or  _/_e_t_c_/_b_l_k_i_d_._t_a_b  on  systems
              without a /run directory.

       _E_V_A_L_U_A_T_E_=_<_m_e_t_h_o_d_s_>
              Defines  LABEL  and  UUID  evaluation method(s).  Currently, the
              libblkid library supports the "udev" and "scan"  methods.   More
              than  one  method  may  be  specified in a comma-separated list.
              Default  is  "udev,scan".    The   "udev"   method   uses   udev
              _/_d_e_v_/_d_i_s_k_/_b_y_-_*  symlinks  and  the "scan" method scans all block
              devices from the _/_p_r_o_c_/_p_a_r_t_i_t_i_o_n_s file.

AAUUTTHHOORR
       bbllkkiidd was written by  Andreas  Dilger  for  libblkid  and  improved  by
       Theodore Ts'o and Karel Zak.

EENNVVIIRROONNMMEENNTT
       Setting LIBBLKID_DEBUG=all enables debug output.

SSEEEE AALLSSOO
       lliibbbbllkkiidd(3), ffiinnddffss(8), llssbbllkk(8), wwiippeeffss(8)

AAVVAAIILLAABBIILLIITTYY
       The  blkid  command  is part of the util-linux package and is available
       from https://www.kernel.org/pub/linux/utils/util-linux/.

util-linux                        March 2013                          BLKID(8)
