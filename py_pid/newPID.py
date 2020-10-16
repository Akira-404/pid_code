import time
import numpy as np
import matplotlib.pyplot as plt
import time


# 限定数值范围，避免越界
def Range(value, limits):
    lower, upper = limits
    if value is None:
        return None
    elif upper is not None and value > upper:
        return upper
    elif lower is not None and value < lower:
        return lower
    return value


_current_time = time.time


class newPID(object):

    def __init__(
            self,
            Kp=1.0,
            Ki=0.0,
            Kd=0.0,
            setpoint=0,  # 设定值
            sample_time=0.01,  # 采样时间
            output_limits=(None, None),  # 输出范围
    ):
        self.Kp, self.Ki, self.Kd = Kp, Ki, Kd
        self.setpoint = setpoint
        self.sample_time = sample_time
        self._min_output, self._max_output = output_limits
        self.reset()
        self.last_error = 0

    # 重置
    def reset(self):
        self.proportional = 0
        self.integral = 0
        self.derivative = 0

        self.last_time = _current_time()
        self.last_output = None
        self.last_real_value = None

    # output范围判断
    @property
    def output_limits(self):
        return self._min_output, self._max_output

    @output_limits.setter
    def output_limits(self, limits):
        if limits is None:
            self._min_output, self._max_output = None, None
            return

        min_output, max_output = limits

        if None not in limits and max_output < min_output:
            raise ValueError('lower limit must be less than upper limit')

        self._min_output = min_output
        self._max_output = max_output

        self.integral = Range(self.integral, self.output_limits)
        self.last_output = Range(self.last_output, self.output_limits)

    # 函数入口：上一次输入值，微分时间
    def calc(self, this_value, dt=None):
        print('---calc---')
        print('this value:',this_value)
        nowtime = _current_time()

        if dt is None:
            dt = nowtime - self.last_time if nowtime - self.last_time else 0.1
        elif dt <= 0:
            raise ValueError('dt has nonpositive value {}. Must be positive.'.format(dt))

        # 如果采样时间不为空 并且 dt小于采样周期 并且上一次输出值也不为空
        # 保证计算时间小于采样时间
        if self.sample_time is not None and dt < self.sample_time and self.last_output is not None:
            return self.last_output

        # 计算误差
        error = self.setpoint - this_value
        # 计算两次真实值误差

        self.proportional = self.Kp * error

        # 计算积分
        self.integral += self.Ki * error * dt  # 累加误差项
        # self.integral = Range(self.integral, self.output_limits)  # 检测范围

        # 计算微分
        # d_input = this_value - (self.last_real_value if self.last_real_value is not None else this_value)
        d_input = error - (self.last_error if self.last_error is not None else 0)
        self.derivative = self.Kd * d_input / dt

        output = self.proportional + self.integral + self.derivative
        # output = Range(output, self.output_limits)  # 检测范围


        print('setpoint:', self.setpoint)
        print('error:', error)
        print('last error:', self.last_error)
        print('-proportional:', self.proportional)
        print('-integral:', self.integral)
        print('-derivative:', self.derivative)
        print('output :', output)
        print('---calc---')
        self.last_output = output
        self.last_real_value = this_value
        self.last_time = nowtime
        self.last_error = error

        return output


class Temperature:
    def __init__(self):
        self.temp = 10

    def update(self, curr, updata_power, dt):
        # curr += updata_power * dt
        curr += updata_power
        noise = np.random.normal(0, 1, 1)
        curr -= 0.2 * noise[0]
        print('noise:', 0.2 * noise[0]*5)
        return curr


if __name__ == '__main__':

    t = Temperature()
    curr_temp = t.temp

    pid = newPID(0.5, 0, 0, setpoint=100)
    # pid.output_limits = (1, 160)

    start_time = time.time()
    last_time = start_time

    setpoint, y, x = [], [], []
    plt.ion()  # 开启一个画图的窗口
    count = 0
    while True:
        # time.sleep(0.1)
        count+=1
        print('count:', count)

        current_time = time.time()
        dt = current_time - last_time

        # power = pid.calc(curr_temp)
        # curr_temp = t.update(curr_temp, power, dt)
        # print('power:', power)
        # print('curr temp:', curr_temp)
        # print('========================')

        x += [current_time]
        y += [curr_temp]
        setpoint.append(100)
        last_time = current_time
        plt.clf()  # 清除之前画的图
        plt.plot(x, y, label='curr')
        plt.plot(x, setpoint, label='target')
        plt.xlabel('time')
        plt.ylabel('temperature')
        plt.pause(0.1)  # 暂停一秒
        plt.legend()
        plt.show()

        power = pid.calc(curr_temp)
        curr_temp = t.update(curr_temp, power, 0.1)
        print('power:', power)
        print('curr temp:', curr_temp)
        print('========================')
