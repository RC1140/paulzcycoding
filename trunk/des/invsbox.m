m = load('sboxmat');
n = abs(inv(m));

dlmwrite('sboxinvmat', n, ' ');

exit;
