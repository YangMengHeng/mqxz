<template>
  <div id="museum">
    <el-row :gutter="10">
      <el-col :span="12">
        <el-card id="areaImageCard1">
                <div class="libDiv">
                  <el-popover
                  placement="bottom-start"
                  title=""
                  width="800"
                  trigger="click"
                  >
                    <img src="../assets/01.jpg" class="areaDetailImage">
                    <div class="internalTextDiv1">
                      <p>实时访问人数：{{currentCount[0].currentCount}}人</p>
                      <p>今日访问人数：{{dayCount[0].dayCount}}人</p>
                      <p>历史访问人数：{{historyCount[0].historyCount}}人</p>
                      <p>本月访问人数：{{monthCount[0].monthCount}}人</p>
                      <p>今年访问人数：{{yearCount[0].yearCount}}人</p>
                    </div>
                    <el-button
                      slot="reference"
                      class="area"
                      circle=""
                      icon="el-icon-s-data"
                      >
                    区域详情</el-button>
                  </el-popover>
                </div>
                <div class="textDiv">
                  <p>实时访问人数：{{currentCount[0].currentCount}}人</p>
                </div>
        </el-card>
      </el-col>

      <el-col :span="12">
        <el-card id="areaImageCard2">
                <div class="libDiv">
                  <el-popover
                  placement="bottom-start"
                  title=""
                  width="800"
                  trigger="click"
                  >
                    <img src="../assets/02.jpg" class="areaDetailImage">
                    <div class="internalTextDiv2">
                      <p>实时访问人数：{{currentCount[1].currentCount}}人</p>
                      <p>今日访问人数：{{dayCount[1].dayCount}}人</p>
                      <p>历史访问人数：{{historyCount[1].historyCount}}人</p>
                      <p>本月访问人数：{{monthCount[1].monthCount}}人</p>
                      <p>今年访问人数：{{yearCount[1].yearCount}}人</p>
                    </div>
                    <el-button
                      slot="reference"
                      class="area"
                      circle=""
                      icon="el-icon-s-data"
                      >
                    区域详情</el-button>
                  </el-popover>
                </div>
                <div class="textDiv">
                  <p>实时访问人数：{{currentCount[1].currentCount}}人</p>
                </div>
        </el-card>
      </el-col>
    </el-row>

    <el-row :gutter="10">
      <el-col :span="12">
        <el-card id="areaImageCard3">
                <div class="libDiv">
                  <el-popover
                  placement="bottom-start"
                  title=""
                  width="800"
                  trigger="click"
                  >
                    <img src="../assets/03.jpg" class="areaDetailImage">
                    <div class="internalTextDiv3">
                      <p>实时访问人数：{{currentCount[2].currentCount}}人</p>
                      <p>今日访问人数：{{dayCount[2].dayCount}}人</p>
                      <p>历史访问人数：{{historyCount[2].historyCount}}人</p>
                      <p>本月访问人数：{{monthCount[2].monthCount}}人</p>
                      <p>今年访问人数：{{yearCount[2].yearCount}}人</p>
                    </div>
                    <el-button
                      slot="reference"
                      class="area"
                      circle=""
                      icon="el-icon-s-data"
                      >
                    区域详情</el-button>
                  </el-popover>
                </div>
                <div class="textDiv">
                  <p>实时访问人数：{{currentCount[2].currentCount}}人</p>
                </div>
        </el-card>
      </el-col>

      <el-col :span="12">
        <el-card id="areaImageCard4">
                <div class="libDiv">
                  <el-popover
                  placement="bottom-start"
                  title=""
                  width="800"
                  trigger="click"
                  >
                    <img src="../assets/04.jpg" class="areaDetailImage">
                    <div class="internalTextDiv4">
                      <p>实时访问人数：{{currentCount[3].currentCount}}人</p>
                      <p>今日访问人数：{{dayCount[3].dayCount}}人</p>
                      <p>历史访问人数：{{historyCount[3].historyCount}}人</p>
                      <p>本月访问人数：{{monthCount[3].monthCount}}人</p>
                      <p>今年访问人数：{{yearCount[3].yearCount}}人</p>
                    </div>
                    <el-button
                      slot="reference"
                      class="area"
                      circle=""
                      icon="el-icon-s-data"
                      >
                    区域详情</el-button>
                  </el-popover>
                </div>
                <div class="textDiv">
                  <p>实时访问人数：{{currentCount[3].currentCount}}人</p>
                </div>
        </el-card>
      </el-col>
    </el-row>
  </div>
</template>

<script>
export default {
  name: "MuseumComponent",
  props: {},
  data() {
    let areaImageUrl = [
      '../assets/01.jpg',
      '../assets/02.jpg',
      '../assets/03.jpg',
      '../assets/04.jpg'
    ]
    let currentCount = [0, 0, 0, 0]
    let dayCount = [0, 0, 0, 0]
    let historyCount = [0, 0, 0, 0]
    let monthCount = [0, 0, 0, 0]
    let yearCount = [0, 0, 0, 0]

    return {areaImageUrl, currentCount, dayCount, historyCount, monthCount, yearCount};
  },
  beforeCreate(){
    this.$axios.get('api/data/area/currentCount')
      .then((result) => {
        console.log('current', result.data)
        this.currentCount = result.data.data
      }).catch((err) => {
        console.log(err)
      });

      this.$axios.get('api/data/area/dayCount')
      .then((result) => {
        console.log('day', result.data)
        this.dayCount = result.data.data
      }).catch((err) => {
        console.log(err)
      });

      this.$axios.get('api/data/area/historyCount')
      .then((result) => {
        console.log('history', result.data)
        this.historyCount = result.data.data
      }).catch((err) => {
        console.log(err)
      });

      this.$axios.get('api/data/area/monthCount')
      .then((result) => {
        console.log('month', result.data)
        this.monthCount = result.data.data
      }).catch((err) => {
        console.log(err)
      });

      this.$axios.get('api/data/area/yearCount')
      .then((result) => {
        console.log('year', result.data)
        this.yearCount = result.data.data
      }).catch((err) => {
        console.log(err)
      });
  }
};
</script>

<style scoped>
#museum {
  font-family: "Helvetica Neue", Helvetica, "PingFang SC", "Hiragino Sans GB",
    "Microsoft YaHei", "微软雅黑", Arial, sans-serif;
}

#areaImageCard1{
  width: 100%;
  height: 100%;
  background-image: url("../assets/01.jpg");
  background-size: cover;
  background-repeat: no-repeat;
}

#areaImageCard2{
  width: 100%;
  height: 100%;
  background-image: url("../assets/02.jpg");
  background-size: cover;
  background-repeat: no-repeat;
}

#areaImageCard3{
  width: 100%;
  height: 100%;
  background-image: url("../assets/03.jpg");
  background-size: cover;
  background-repeat: no-repeat;
}

#areaImageCard4{
  width: 100%;
  height: 100%;
  background-image: url("../assets/04.jpg");
  background-size: cover;
  background-repeat: no-repeat;
}

.libDiv{
  position: relative;
  z-index: 99;
  font-size: 30px;
}

.internalTextDiv1{
  top: 10px;
  left: 300px;
  position: absolute;
  z-index: 99;
  font-size: 24px;
  color: black;
}

.internalTextDiv2{
  top: 10px;
  left: 300px;
  position: absolute;
  z-index: 99;
  font-size: 24px;
  color: black;
}

.internalTextDiv3{
  top: 10px;
  left: 300px;
  position: absolute;
  z-index: 99;
  font-size: 24px;
  color: black;
}

.internalTextDiv4{
  top: 10px;
  left: 300px;
  position: absolute;
  z-index: 99;
  font-size: 24px;
  color: black;
}

.textDiv{
  position: relative;
  z-index: 99;
  font-size: 32px;
  color: white;
}

.areaImage{
  width: 100%;
  height: 100%;
  opacity: 0.9;
  z-index: 0;
}

.areaDetailImage{
  width: 100%;
  height: 100%;
  opacity: 0.4;
  position: relative;
  z-index: 0;
}
</style>
