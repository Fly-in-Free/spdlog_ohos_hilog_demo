import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libentry.so';

@Entry
@Component
struct Index {
  @State message: string = 'Hello World';

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            const baseFileName = getContext(this).filesDir + '/logs/log_base_name.log'
            testNapi.testSpdLogNapi(baseFileName)
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
