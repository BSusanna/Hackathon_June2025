#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class RandomForest {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        uint8_t votes[2] = { 0 };
                        // tree #1
                        if (x[0] <= 29.890013694763184) {
                            if (x[0] <= 20.072338104248047) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #2
                        if (x[0] <= 29.87545108795166) {
                            if (x[0] <= 19.93634605407715) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #3
                        if (x[0] <= 20.01074504852295) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.936135292053223) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #4
                        if (x[0] <= 19.93837547302246) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.87545108795166) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #5
                        if (x[0] <= 20.008352279663086) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.867328643798828) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #6
                        if (x[0] <= 20.318066596984863) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.87545108795166) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #7
                        if (x[0] <= 29.936135292053223) {
                            if (x[0] <= 20.072338104248047) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // tree #8
                        if (x[0] <= 19.93837547302246) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.837675094604492) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #9
                        if (x[0] <= 20.072338104248047) {
                            votes[1] += 1;
                        }

                        else {
                            if (x[0] <= 29.87545108795166) {
                                votes[0] += 1;
                            }

                            else {
                                votes[1] += 1;
                            }
                        }

                        // tree #10
                        if (x[0] <= 29.87545108795166) {
                            if (x[0] <= 20.01074504852295) {
                                votes[1] += 1;
                            }

                            else {
                                votes[0] += 1;
                            }
                        }

                        else {
                            votes[1] += 1;
                        }

                        // return argmax of votes
                        uint8_t classIdx = 0;
                        float maxVotes = votes[0];

                        for (uint8_t i = 1; i < 2; i++) {
                            if (votes[i] > maxVotes) {
                                classIdx = i;
                                maxVotes = votes[i];
                            }
                        }

                        return classIdx;
                    }

                protected:
                };
            }
        }
    }