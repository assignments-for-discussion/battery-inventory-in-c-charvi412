#include <stdio.h>
#include <assert.h>

struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};
    for (int i = 0; i < nBatteries; i++) {
      double SoH;
      
      // Check if the present capacity is greater than rated capacity (120 Ah).
      if (presentCapacities[i] > 120) {
          // Battery is performing better than rated capacity, SoH is greater than 100%.
          SoH = ((double)presentCapacities[i] / 120.0) * 100.0;
      } else {
          // Calculate SoH using the standard formula.
          SoH = ((double)presentCapacities[i] / 120.0) * 100.0;
      }
      
      // Check the SoH value to classify the battery.
      if (SoH > 80.0) {
          counts.healthy++;
      } else if (SoH >= 65.0) {
          counts.exchange++;
      } else {
          counts.failed++;
      }
  }
 return counts;
}


 void testBucketingByHealth() {
  const int presentCapacities[] = {115, 118, 80, 95, 91, 77};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  
  printf("Counting batteries by SoH...\n");
  
  // Test case 1: Basic test case with sample data.
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);
  
  // Assert that the counts match the expected values.
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);
  
  // Test case 2: Boundary condition - All batteries are healthy (SoH = 100%).
  const int allHealthyCapacities[] = {120, 120, 120, 120};
  const int numberOfAllHealthyBatteries = sizeof(allHealthyCapacities) / sizeof(allHealthyCapacities[0]);
  struct CountsBySoH allHealthyCounts = countBatteriesByHealth(allHealthyCapacities, numberOfAllHealthyBatteries);
  assert(allHealthyCounts.healthy == numberOfAllHealthyBatteries);
  assert(allHealthyCounts.exchange == 0);
  assert(allHealthyCounts.failed == 0);
  
  // Test case 3: Boundary condition - All batteries are failed (SoH = 0%).
  const int allFailedCapacities[] = {0, 0, 0, 0};
  const int numberOfAllFailedBatteries = sizeof(allFailedCapacities) / sizeof(allFailedCapacities[0]);
  struct CountsBySoH allFailedCounts = countBatteriesByHealth(allFailedCapacities, numberOfAllFailedBatteries);
  assert(allFailedCounts.healthy == 0);
  assert(allFailedCounts.exchange == 0);
  assert(allFailedCounts.failed == numberOfAllFailedBatteries);
  
  // Add more test cases as needed...

  printf("Done counting :)\n");
}

int main() {
  testBucketingByHealth();
  return 0;
}
