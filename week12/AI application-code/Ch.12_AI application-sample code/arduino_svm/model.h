#pragma once
//#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class SVM {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        float kernels[14] = { 0 };
                        float decisions[1] = { 0 };
                        int votes[2] = { 0 };
                        kernels[0] = compute_kernel(x,   -1.51  , -5.83  , 0.9  , -1.43  , -9.42  , 0.53  , -2.99  , -10.88  , -1.75  , -1.57  , -8.7  , -2.32  , -1.03  , -4.11  , -3.53  , 3.09  , 2.73  , -1.92  , 7.18  , 9.05  , 2.08  , 6.82  , 12.1  , 10.4  , 3.36  , 12.45  , 3.62  , -0.63  , 8.31  , -2.64  , -1.94  , 5.24  , -0.75  , 0.47  , 2.75  , 0.96  , 0.86  , -0.96  , 1.61  , 0.65  , -3.21  , 1.0  , -0.51  , -4.05  , -2.5  , -0.55  , -4.08  , -1.47  , -0.25  , -3.14  , -1.61  , -0.04  , -3.04  , -2.12  , -0.24  , -2.76  , 1.56  , 0.15  , -1.84  , 1.14  , 1.51  , -0.33  , -1.87  , 1.0  , -0.23  , 0.59  , 0.31  , -0.49  , 1.21  , -0.24  , -0.22  , -0.97  , 0.7  , 0.49  , -1.0  , 1.08  , 0.4  , 0.96  , 0.42  , 0.36  , -0.77  , 0.67  , 0.49  , -0.99  , 0.75  , 0.36  , 0.41  , 0.37  , 0.2  , 0.2 );
                        kernels[1] = compute_kernel(x,   1.99  , -4.15  , 1.93  , 1.37  , -9.45  , 0.37  , -0.09  , -12.37  , -3.61  , -0.67  , -11.21  , 0.24  , -0.72  , -5.97  , -0.82  , 2.46  , 0.96  , -4.27  , 3.42  , 5.9  , -1.2  , 3.28  , 10.8  , 2.26  , 3.12  , 15.6  , 3.09  , 3.0  , 14.49  , 3.64  , 0.39  , 8.74  , 1.79  , -0.84  , 4.18  , -0.85  , -0.46  , 1.96  , 1.03  , 1.95  , 1.14  , 0.14  , 2.79  , -0.1  , -0.8  , 1.01  , -2.52  , 0.24  , 0.39  , -3.8  , -1.28  , -0.26  , -5.07  , 1.91  , 0.38  , -4.24  , -1.28  , 0.16  , -3.16  , -1.87  , -0.12  , -2.28  , 1.13  , -0.16  , -1.52  , -0.24  , -0.02  , -0.66  , -2.35  , 0.16  , 0.05  , -0.32  , 0.78  , 0.41  , 1.06  , 0.72  , 0.51  , 0.41  , -0.0  , 0.63  , -0.36  , 0.06  , 0.75  , -0.47  , 0.0  , 0.96  , -1.43  , 0.49  , 0.61  , 0.87 );
                        kernels[2] = compute_kernel(x,   3.73  , -2.12  , -0.27  , -1.01  , -4.96  , -1.24  , -3.09  , -6.32  , -2.98  , 1.39  , -4.52  , -0.95  , -0.12  , -3.75  , 0.83  , -1.04  , -3.37  , -1.15  , 0.49  , -1.83  , -0.99  , 1.16  , -0.36  , 0.83  , 0.55  , 0.29  , 0.58  , 0.12  , 0.48  , -0.27  , 0.44  , 0.65  , -0.09  , 0.21  , 0.39  , -0.06  , -0.23  , 0.2  , -0.91  , -0.26  , 0.06  , -0.34  , -0.01  , -0.04  , 0.75  , -0.09  , 0.31  , -0.9  , -0.29  , 0.27  , -0.86  , -0.13  , -0.04  , 1.01  , 0.09  , 0.15  , -0.48  , -0.09  , 0.16  , -0.95  , -0.18  , -0.06  , 0.71  , -0.06  , 0.21  , -0.49  , -0.07  , 0.33  , -0.57  , -0.2  , 0.0  , 0.32  , -0.18  , -0.16  , -0.1  , -0.22  , -0.13  , -0.84  , -0.11  , 0.04  , -0.32  , -0.24  , -0.04  , -0.02  , -0.2  , -0.06  , -0.27  , 0.17  , 0.29  , -0.7 );
                        kernels[3] = compute_kernel(x,   2.47  , -2.35  , -1.22  , -1.29  , -4.41  , -1.76  , -1.09  , -5.01  , 0.43  , -0.06  , -3.97  , 0.72  , -0.69  , -2.77  , -1.95  , -1.02  , -2.57  , -0.2  , -0.86  , -2.02  , -0.06  , -0.1  , -0.91  , -1.01  , -0.22  , -0.27  , -1.21  , -0.22  , 0.1  , -1.36  , 0.58  , 0.61  , 0.33  , -0.14  , 0.32  , 0.43  , 0.09  , 0.47  , -0.22  , -0.25  , 0.48  , -0.36  , -0.0  , 0.5  , 0.2  , -0.08  , 0.58  , -0.06  , -0.17  , 0.56  , -0.59  , -0.46  , 0.24  , -0.2  , 0.38  , 0.49  , 0.96  , 0.02  , 0.73  , -0.64  , -0.35  , 0.4  , -0.22  , -0.34  , 0.27  , 0.13  , 0.3  , 0.45  , -0.16  , -0.07  , 0.35  , -0.57  , -0.28  , 0.26  , -0.59  , -0.3  , 0.16  , -0.38  , -0.03  , 0.3  , -0.51  , -0.03  , 0.3  , 0.19  , -0.1  , 0.14  , -0.14  , -0.11  , 0.24  , -0.37 );
                        kernels[4] = compute_kernel(x,   0.28  , -11.86  , 2.56  , 2.56  , 2.24  , -2.25  , 6.45  , 15.18  , 2.66  , 6.37  , 19.14  , 1.72  , 0.68  , 13.73  , 3.63  , -3.18  , 7.93  , 0.46  , -3.74  , 6.04  , -1.14  , 1.03  , 6.9  , -1.61  , 2.09  , 4.39  , 1.67  , 2.67  , 1.31  , 1.95  , 4.31  , -0.29  , -0.81  , -0.87  , -3.36  , -1.16  , -2.41  , -4.52  , -0.29  , 0.86  , -3.79  , -0.01  , -0.75  , -3.7  , -1.39  , -1.01  , -3.89  , -0.07  , -0.07  , -3.25  , 0.85  , 0.07  , -1.71  , -2.39  , 0.39  , -0.82  , -0.06  , 0.95  , -0.12  , 0.14  , 0.39  , -0.08  , -0.43  , 0.22  , -0.09  , 0.15  , 0.16  , -0.01  , -0.24  , 0.5  , 0.35  , -0.85  , 0.59  , 0.58  , -0.29  , 0.55  , 0.39  , 0.41  , 0.07  , 0.29  , -0.17  , 0.33  , 0.53  , -0.42  , 0.32  , 0.43  , -0.17  , 0.12  , 0.19  , -0.29 );
                        kernels[5] = compute_kernel(x,   1.12  , 7.96  , 0.52  , 1.34  , 2.93  , 1.73  , 4.74  , 0.17  , 0.1  , 1.81  , -3.3  , -0.14  , 0.35  , -5.19  , -1.23  , -0.33  , -6.08  , -0.52  , -1.35  , -5.18  , -0.17  , -1.01  , -3.55  , -2.86  , 0.54  , -2.09  , 0.33  , 0.75  , -1.13  , -0.71  , 0.08  , -1.38  , 0.17  , -0.3  , -1.19  , 0.7  , -0.17  , -0.51  , -0.78  , 0.7  , 0.24  , 0.28  , 0.38  , 0.63  , -0.83  , -0.16  , 0.13  , -1.19  , 0.02  , -0.03  , 0.75  , 0.28  , 0.16  , -0.06  , 0.06  , 0.26  , -0.79  , -0.05  , 0.33  , -0.49  , 0.21  , 0.42  , 0.25  , 0.35  , 0.49  , -0.12  , 0.26  , 0.56  , -0.62  , 0.12  , 0.37  , -0.63  , 0.06  , 0.19  , -0.17  , -0.08  , 0.04  , -0.11  , 0.11  , 0.23  , -0.48  , 0.34  , 0.23  , -0.43  , 0.17  , 0.04  , 0.11  , 0.04  , 0.11  , -0.47 );
                        kernels[6] = compute_kernel(x,   -0.97  , -5.08  , 0.71  , -1.34  , -5.38  , -0.74  , -0.17  , -4.24  , -0.12  , -1.73  , -3.98  , -0.34  , 0.02  , -2.34  , -0.84  , 0.06  , -0.91  , -0.17  , 0.09  , -0.08  , -0.42  , 0.12  , 0.09  , -0.53  , 0.34  , 0.23  , -0.22  , -0.23  , 0.09  , -0.14  , -0.39  , 0.32  , -0.06  , -0.46  , 0.37  , -0.35  , 0.05  , 0.58  , -0.9  , -0.6  , 0.28  , -0.11  , -0.73  , 0.05  , -0.08  , -0.38  , 0.16  , -0.76  , -0.11  , 0.16  , -0.32  , -0.6  , -0.1  , 0.13  , -0.57  , -0.07  , -0.02  , -0.46  , 0.26  , -0.6  , -0.05  , 0.4  , -0.54  , -0.49  , -0.1  , 0.18  , -0.51  , -0.06  , -0.29  , -0.12  , 0.27  , -0.46  , -0.06  , 0.25  , 0.19  , -0.33  , 0.17  , -0.23  , -0.4  , 0.21  , -0.37  , 0.01  , 0.23  , 0.14  , -0.39  , 0.11  , 0.02  , -0.39  , 0.14  , -0.14 );
                        kernels[7] = compute_kernel(x,   4.34  , 13.56  , 4.62  , -2.51  , 9.58  , 4.76  , -2.98  , 11.47  , -1.47  , 1.73  , 13.1  , -0.34  , 1.53  , 9.77  , -0.12  , 1.0  , 3.13  , 1.34  , 1.44  , -1.34  , 0.06  , 2.76  , -4.55  , -1.07  , -1.11  , -7.39  , -0.31  , -2.36  , -7.11  , -2.58  , 3.84  , -3.35  , -1.15  , -0.35  , -4.15  , 2.54  , -1.95  , -3.72  , -0.94  , 0.64  , -1.11  , -1.87  , 2.86  , -0.37  , 1.4  , -0.45  , -1.22  , 0.35  , -0.48  , -0.74  , -1.41  , 0.99  , 0.12  , -0.01  , 0.99  , 0.11  , 0.43  , -0.46  , -0.03  , -1.25  , -0.24  , -0.19  , -0.14  , 0.22  , 0.03  , 0.61  , 0.16  , 0.17  , -0.47  , -0.34  , -0.15  , -0.4  , -0.01  , -0.06  , -0.02  , 0.0  , 0.09  , -0.86  , 0.19  , 0.12  , -0.67  , 0.17  , -0.05  , -0.16  , -0.17  , -0.17  , -0.03  , -0.02  , -0.09  , 0.07 );
                        kernels[8] = compute_kernel(x,   4.91  , -1.1  , -0.51  , 6.15  , -1.72  , 0.52  , 0.11  , -1.14  , 1.91  , -8.29  , -0.62  , 1.5  , -8.53  , -0.55  , 0.11  , -2.91  , -0.48  , 0.01  , 0.6  , -0.06  , -0.87  , 1.12  , -0.16  , -0.28  , 0.06  , -0.47  , -0.21  , 1.18  , -0.94  , -0.63  , 1.42  , -1.13  , -0.22  , 1.46  , -1.34  , 0.98  , 0.09  , -1.0  , 0.72  , 0.52  , -0.99  , 0.84  , -0.7  , -0.6  , 0.22  , -0.79  , -0.51  , -0.1  , -0.82  , -0.51  , -0.14  , -1.03  , -0.54  , 0.31  , -0.32  , -0.57  , 0.01  , -0.55  , -0.61  , 0.09  , -0.08  , -0.8  , 0.06  , -0.36  , -0.65  , 0.31  , -0.13  , -0.78  , 0.14  , 0.06  , -0.83  , 0.45  , -0.13  , -0.77  , 0.18  , -0.13  , -0.68  , 0.3  , -0.48  , -0.7  , 0.16  , -0.41  , -0.7  , -0.04  , -0.88  , -0.64  , 0.0  , -0.36  , -0.63  , 0.08 );
                        kernels[9] = compute_kernel(x,   -4.54  , -1.71  , 1.68  , -20.0  , 2.69  , 6.21  , -8.59  , -0.02  , -0.72  , -4.05  , -0.27  , 1.28  , 0.4  , -0.13  , -0.79  , 2.41  , -0.37  , 0.72  , -0.16  , -0.27  , 0.12  , 1.55  , -1.32  , -0.99  , -0.16  , -1.39  , 0.27  , 0.45  , -1.51  , 0.92  , 0.74  , -1.53  , 1.3  , 1.03  , -1.15  , 0.22  , 0.35  , -0.81  , -0.26  , -0.85  , -0.61  , -0.36  , -1.03  , -0.63  , -0.3  , -0.64  , -0.87  , 0.29  , -0.66  , -0.89  , 0.14  , -0.13  , -0.93  , 0.26  , 0.14  , -0.89  , 0.41  , -0.22  , -0.93  , 0.48  , 0.41  , -0.99  , 0.1  , -0.23  , -0.92  , 0.0  , -0.37  , -1.04  , 0.41  , -0.39  , -0.96  , 0.19  , -0.44  , -0.87  , -0.33  , -0.39  , -0.79  , 0.06  , -0.03  , -0.78  , -0.08  , -0.56  , -0.67  , -0.11  , -0.49  , -0.76  , 0.11  , -0.3  , -0.78  , 0.55 );
                        kernels[10] = compute_kernel(x,   1.54  , -1.86  , 2.05  , 0.84  , -1.27  , 0.62  , 0.74  , -0.83  , -0.51  , -0.5  , -0.47  , -0.35  , -0.24  , -0.5  , -0.44  , -1.14  , -0.43  , -0.15  , -0.8  , -0.41  , 0.01  , -1.04  , -0.44  , 0.05  , -0.58  , -0.67  , 0.31  , 0.59  , -0.94  , 0.86  , -0.13  , -0.86  , 0.32  , 0.27  , -0.89  , 0.05  , 0.29  , -0.81  , 0.48  , -0.66  , -0.67  , -0.01  , -0.15  , -0.78  , 0.04  , -0.68  , -0.65  , 0.26  , -0.43  , -0.67  , -0.39  , -0.54  , -0.62  , 0.05  , -0.92  , -0.39  , -0.33  , -0.37  , -0.58  , 0.15  , -0.15  , -0.71  , 0.65  , 0.49  , -0.95  , 0.82  , -0.21  , -0.88  , 0.66  , -0.55  , -0.93  , 0.45  , 0.46  , -1.0  , 0.37  , -0.73  , -0.62  , -0.52  , -0.39  , -0.53  , -0.08  , -0.14  , -0.69  , -0.11  , -0.36  , -0.68  , 0.15  , -0.29  , -0.72  , 0.24 );
                        kernels[11] = compute_kernel(x,   4.66  , -1.3  , -0.26  , 5.39  , -2.03  , 0.96  , 0.26  , -1.77  , 1.67  , -3.22  , -1.25  , 0.85  , -7.67  , -0.17  , 0.09  , -9.57  , 0.28  , -0.86  , -2.41  , -0.47  , -1.33  , 1.51  , -0.46  , 0.76  , 2.09  , -0.43  , 1.08  , 1.72  , -0.78  , -0.44  , 1.7  , -1.41  , -0.39  , 2.25  , -1.34  , -0.78  , 2.51  , -1.41  , 2.17  , 0.52  , -1.39  , 1.58  , -1.12  , -0.77  , -0.82  , -0.88  , -0.53  , -0.57  , -0.36  , -0.55  , -0.03  , 0.03  , -0.61  , -0.22  , 0.19  , -0.75  , 0.47  , 0.04  , -0.81  , 0.16  , -0.52  , -0.88  , 0.25  , -0.31  , -0.82  , 0.07  , 0.54  , -1.0  , 0.35  , -0.55  , -0.7  , -0.02  , 0.33  , -0.84  , 0.11  , 0.23  , -0.87  , 0.15  , -0.45  , -0.73  , -0.07  , 0.01  , -0.85  , 0.69  , 0.01  , -0.76  , -0.11  , -0.34  , -0.69  , 0.05 );
                        kernels[12] = compute_kernel(x,   3.91  , -0.5  , -0.93  , 8.79  , -1.07  , -0.34  , 3.56  , -2.22  , 1.33  , -6.94  , -1.84  , 3.26  , -10.03  , -1.02  , 1.09  , -5.95  , -0.27  , -1.1  , -1.56  , -0.03  , -1.81  , 2.85  , -0.25  , -0.73  , 2.47  , -0.55  , 0.63  , 2.12  , -0.93  , -0.33  , 1.43  , -1.25  , 0.33  , 0.81  , -1.6  , 0.95  , -0.04  , -1.39  , 0.81  , 0.21  , -1.01  , 0.23  , 0.16  , -0.79  , -0.02  , -0.5  , -0.59  , -0.08  , -0.85  , -0.48  , -0.49  , -0.34  , -0.56  , -0.21  , -0.38  , -0.72  , -0.07  , -0.32  , -0.84  , -0.1  , 0.02  , -0.85  , 0.63  , 0.05  , -0.94  , 0.47  , 0.31  , -0.95  , 0.52  , 0.04  , -0.89  , 0.53  , -0.15  , -0.84  , 0.26  , -0.17  , -0.81  , -0.12  , 0.01  , -0.7  , 0.02  , -0.59  , -0.69  , -0.18  , -0.03  , -0.84  , 0.08  , -0.21  , -0.73  , 0.29 );
                        kernels[13] = compute_kernel(x,   5.71  , -0.77  , 0.96  , 4.86  , -0.56  , -0.66  , 2.74  , -0.89  , -0.75  , 2.29  , -1.93  , -0.06  , 0.19  , -1.92  , 1.28  , -0.11  , -1.42  , 1.1  , 0.68  , -1.03  , 0.33  , -0.21  , -0.61  , 0.21  , 0.15  , -0.72  , 1.1  , -1.01  , -0.44  , -0.37  , -0.73  , -0.5  , -0.33  , -0.59  , -0.6  , -0.27  , 0.2  , -0.91  , 0.46  , 0.45  , -0.97  , 0.52  , 0.83  , -1.13  , 0.44  , 0.62  , -1.16  , 0.66  , 0.14  , -0.99  , 0.02  , 0.0  , -0.95  , -0.19  , -0.34  , -0.83  , -0.12  , -0.04  , -0.77  , 0.09  , -0.21  , -0.73  , 0.1  , -0.04  , -0.74  , -0.24  , -0.31  , -0.77  , 0.11  , 0.16  , -0.88  , 0.44  , -0.13  , -0.87  , 0.16  , 0.36  , -0.9  , 0.28  , 0.19  , -0.86  , 0.63  , -0.07  , -0.83  , -0.12  , -0.54  , -0.74  , -0.15  , 0.1  , -0.84  , 0.11 );
                        float decision = -0.600098725484;
                        decision = decision - ( + kernels[0] * -0.427783008657  + kernels[1] * -0.149936868637  + kernels[2] * -1.0  + kernels[3] * -1.0  + kernels[4] * -0.530311600173  + kernels[5] * -1.0  + kernels[6] * -1.0  + kernels[7] * -0.817791950543 );
                        decision = decision - ( + kernels[8] * 1.0  + kernels[9] * 1.0  + kernels[10] * 1.0  + kernels[11] * 1.0  + kernels[12] * 0.92582342801  + kernels[13] * 1.0 );

                        return decision > 0 ? 0 : 1;
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "left";
                            case 1:
                            return "right";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                    /**
                    * Compute kernel between feature vector and support vector.
                    * Kernel type: poly
                    */
                    float compute_kernel(float *x, ...) {
                        va_list w;
                        va_start(w, 90);
                        float kernel = 0.0;

                        for (uint16_t i = 0; i < 90; i++) {
                            kernel += x[i] * va_arg(w, double);
                        }

                        return pow((0.002 * kernel) + 0.0, 1);
                    }
                };
            }
        }
    }
