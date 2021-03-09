#pragma once

struct Statistics {
  long uTime {0};
  long sTime {0};
  long cuTime {0};
  long csTime {0};
  long startTime {0};

  long totalTime() { return uTime + sTime + cuTime + csTime; }
};